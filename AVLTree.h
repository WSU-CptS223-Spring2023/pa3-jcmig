#ifndef AVLTREE_H
#define AVLTREE_H

#include "AVLNode.h"

#include <fstream>
#include <sstream>
#include <vector>
using std::ifstream;
using std::stringstream;
using std::getline;
using std::vector;
using std::cerr;

template<typename T>
class AVLTree {
public:
    AVLTree() : root_(nullptr) {}
    AVLTree(const AVLTree& other) { copyHelper(other.root_, root_); }
    AVLTree(AVLTree&& other) noexcept { moveHelper(other.root_, root_); other.root_ = nullptr; }
    ~AVLTree() { clear(); }

    int isEmpty() const { return (root_==nullptr) ? 1 : 0; }
    
    int height(AVLNode<T>* node) const {
        if (node == nullptr) {
            return -1;
        }
        return node->getHeight();
    }
    
    void insert(const T& data) { root_ = insertHelper(root_, data); }

    bool remove(const T& key) { bool removed = false; root_ = removeHelper(root_, key, removed); return removed;}

    void clear() { clearHelper(root_); }

    T findMin() const { findMinHelper(); }

    T findMax() const { findMaxHelper(); }

    void printInOrder() const { printInOrderHelper(root_); }

    vector<T> inOrder(vector<T> result) const { result; inOrderHelper(root_, result); return result; }

private:
    AVLNode<T>* root_;

    void copyHelper(const AVLNode<T>* src, AVLNode<T>*& dest) const {
        if (src == nullptr) { 
            dest = nullptr; 
        } else { 
            dest = new AVLNode<T>(src->getData());
            copyHelper(src->getLeft(), dest->getLeft()); 
            copyHelper(src->getRight(), dest->getRight()); 
        }
    }

    void moveHelper(AVLNode<T>* src, AVLNode<T>*& dest) noexcept { dest = src; src = nullptr; }

    AVLNode<T>* insertHelper(AVLNode<T>* node, const T& data) {
        if (node == nullptr) {
            AVLNode<T>* newNode = new AVLNode<T>(data);
            return newNode;
        }
        
        if (data.getRate() < node->getData().getRate()) {
            node->setLeft(insertHelper(node->getLeft(), data));
        } else {
            node->setRight(insertHelper(node->getRight(), data));
        }

        node->setHeight(max(height(node->getLeft()), height(node->getRight())) + 1);
        int balanceFactor = height(node->getLeft()) - height(node->getRight());
        if (balanceFactor > 1) {
            if (height(node->getLeft()->getLeft()) >= height(node->getLeft()->getRight())) {
                node = rightRotate(node);
            } else {
                node->setLeft(leftRotate(node->getLeft()));
                node = rightRotate(node);
            }
        } else if (balanceFactor < -1) {
            if (height(node->getRight()->getRight()) >= height(node->getRight()->getLeft())) {
                node = leftRotate(node);
            } else {
                node->setRight(rightRotate(node->getRight()));
                node = leftRotate(node);
            }
        }

        return node;
    }

    AVLNode<T>* removeHelper(AVLNode<T>* node, const T& key, bool& removed) {
        if (!node)
            return nullptr;

        if (key < node ->getData()) {
            node->setLeft(removeHelper(node->getLeft(), key, removed));
        } else if (key > node->getData()) {
            node->setRight(removeHelper(node->getRight(), key, removed));
        } else {
            AVLNode<T>* leftChild = node->getLeft();
            AVLNode<T>* rightChild = node->getRight();

            if (!leftChild && !rightChild) {
                delete node;
                removed = true;
                return nullptr;
            } else if (!leftChild) {
                AVLNode<T>* temp = node;
                node = rightChild;
                temp->setRight(nullptr);
                delete temp;
                removed = true;
            } else if (!rightChild) {
                AVLNode<T>* temp = node;
                node = leftChild;
                temp->setLeft(nullptr);
                delete temp;
                removed = true;
            } else {
                AVLNode<T>* minNode = findMin(rightChild);
                node->setData(minNode->getData());
                node->setRight(removeHelper(rightChild, minNode->getData(), removed));
            }
        }

        if (!node)
            return nullptr;

        int balanceFactor = height(node->getLeft()) - height(node->getRight());

        if (balanceFactor == 2) {
            if (height(node->getLeft()->getLeft()) >= height(node->getLeft()->getRight())) {
                node = rightRotate(node);
            } else {
                node->setLeft(leftRotate(node->getLeft()));
                node = rightRotate(node);
            }
        } else if (balanceFactor == -2) {
            if (height(node->getRight()->getRight() >= height(node->getRight()->getLeft()))) {
                node = leftRotate(node);
            } else {
                node->setRight(rightRotate(node->getRight()));
                node = leftRotate(node);
            }

            node->setHeight(max(height(node->getLeft()), height(node->getRight())) + 1);

            return node;
        }
    }

    void clearHelper(AVLNode<T>* node) {
        if (node != nullptr) {
            clearHelper(node->getLeft());
            clearHelper(node->getRight());
            delete node;
        }
        root_ = nullptr;
    }

    T findMinHelper() const {
        if (isEmpty()) {
            throw std::logic_error("Tree is empty");
        }
        
        AVLNode<T>* current = root_;
        while (current->getLeft() != nullptr) {
            current = current->getLeft();
        }

        return current->getData();
    }

    T findMaxHelper() const {
        if (isEmpty()) {
            throw std::logic_error("Tree is empty");
        }

        AVLNode<T>* current = root_;
        while (current->getRight() != nullptr) {
            current = current->getRight();
        }

        return current->getData();
    }

    void printInOrderHelper(AVLNode<T>* node) const {
        if (node) {
            printInOrderHelper(node->getLeft());
            cout << node->getData() << endl;
            printInOrderHelper(node->getRight());
        }
    }

    void inOrderHelper(AVLNode<T>* node, vector<T>& result) const {
        if (node) {
            inOrderHelper(node->getLeft(), result);
            result.push_back(node->getData());
            inOrderHelper(node->getRight(), result);
        }
    }

    AVLNode<T>* rightRotate(AVLNode<T>* node) {
        AVLNode<T>* newRoot = node->getLeft();
        AVLNode<T>* rightSubtree = newRoot->getRight();
        newRoot->setRight(node);
        node->setLeft(rightSubtree);
        node->setHeight(max(height(node->getLeft()), height(node->getRight())) + 1);
        newRoot->setHeight(max(height(newRoot->getLeft()), height(newRoot->getRight())) + 1);
        return newRoot;
    }

    AVLNode<T>* leftRotate(AVLNode<T>* node) {
        AVLNode<T>* newRoot = node->getRight();
        AVLNode<T>* leftSubtree = newRoot->getLeft();
        newRoot->setLeft(node);
        node->setRight(leftSubtree);
        node->setHeight(max(height(node->getLeft()), height(node->getRight())) + 1);
        newRoot->setHeight(max(height(newRoot->getLeft()), height(newRoot->getRight())) + 1);
        return newRoot;
    }


};

#endif AVLTREE_H
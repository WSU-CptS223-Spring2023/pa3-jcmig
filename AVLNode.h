#ifndef AVLNODE_H
#define AVLNODE_H

#include "CancerData.h"

template <typename T>
class AVLNode {
public:
    AVLNode() : data(), left(nullptr), right(nullptr), height(0) {}
    AVLNode(const T& d) : data(d), left(nullptr), right(nullptr), height(0) {}
    AVLNode(const AVLNode<T>& other) : data(other.data), left(nullptr), right(nullptr), height(other.height) {}
    AVLNode(AVLNode<T>&& other) noexcept : data(move(other.data)), left(other.left), right(other.right), height(other.height) {
        other.left = nullptr;
        other.right = nullptr;
        other.height = 0;
    }
    AVLNode<T>& operator=(const AVLNode<T>& other) {
        if (this != &other) {
            data = other.data;
            left = nullptr;
            right = nullptr;
            height = other.height;
        }
        return *this;
    }
    AVLNode<T>& operator=(AVLNode<T>&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            left = other.left;
            right = other.right;
            height = other.height;
            other.left = nullptr;
            other.right = nullptr;
            other.height = 0;
        }
        return *this;
    }
    ~AVLNode() {}

    T& getData() { return data; }
    void setData(const T& d) { data = d; }
    AVLNode<T>* getLeft() const { return left; }
    AVLNode<T>* getRight() const { return right; }
    int getHeight() const { return height; }

    void setLeft(AVLNode<T>* node) { left = node; }
    void setRight(AVLNode<T>* node) { right = node; }
    void setHeight(int h) { height = h; }

private:
    T data;
    AVLNode<T>* left;
    AVLNode<T>* right;
    int height;
};

#endif  AVLNODE_H
#ifndef AVLNODE_H
#define AVLNODE_H

#include "CancerData.h"

template <typename T>
class AVLNode {
public:
    AVLNode() : data(), left(nullptr), right(nullptr), height(0) {}
    AVLNode(const T& d) : data(d), left(nullptr), right(nullptr), height(0) {}
    AVLNode(const AVLNode& other) : data(other.data), left(nullptr), right(nullptr), height(other.height) {}
    AVLNode(AVLNode&& other) noexcept : data(std::move(other.data)), left(other.left), right(other.right), height(other.height) {
        other.left = nullptr;
        other.right = nullptr;
        other.height = 0;
    }
    AVLNode& operator=(const AVLNode& other) {
        if (this != &other) {
            data = other.data;
            left = nullptr;
            right = nullptr;
            height = other.height;
        }
        return *this;
    }
    AVLNode& operator=(AVLNode&& other) noexcept {
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
    AVLNode* getLeft() const { return left; }
    void setLeft(AVLNode* node) { left = node; }
    AVLNode* getRight() const { return right; }
    void setRight(AVLNode* node) { right = node; }
    int getHeight() const { return height; }
    void setHeight(int h) { height = h; }

private:
    T data;
    AVLNode* left;
    AVLNode* right;
    int height;
};

#endif  // AVLNODE_H
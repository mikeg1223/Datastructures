#pragma once

#include <memory>

#include "node.h"

namespace mgg{

template<typename T>
class BinarySearchTree{
public:
    void insert(std::shared_ptr<T> data);
    void remove(std::shared_ptr<T> data);
    bool contains(std::shared_ptr<T> data);

private:
    std::unique_ptr<BinaryTreeNode<T>> _sentinel;

}; // class BinarySearchTree

template<typename T>
class RedBlackBinarySearchTree;

template<typename T>
class AVLBinarySearchTree;

template<typename T>
class SplayBinarySearchTree;

} // namespace mgg


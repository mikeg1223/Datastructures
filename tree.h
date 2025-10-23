#pragma once

#include <memory>

#include "node.h"

namespace mgg{

template<typename T>
class BinarySearchTree{
public:
    void insert(BinaryTreeNode<T>& node);
    void remove(BinaryTreeNode<T>& node);
    bool contains(BinaryTreeNode<T>& node);

private:
    std::unique_ptr<BinaryTreeNode<T>> _root;

}; // class BinarySearchTree
} // namespace mgg


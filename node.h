#pragma once

#include <memory>

namespace mgg{

template <typename T>
struct  Node{
    std::shared_ptr<T> data;
}; // Node

template <typename T>
struct LinkedListNode : public Node<T> {
    std::unique_ptr<LinkedListNode<T>> next;
} // LinkedListNode

template <typename T>
struct DoublyLinkedListNode : public Node<T> {
    std::unique_ptr<DoublyLinkedListNode<T>> next;
    std::unique_ptr<DoublyLinkedListNode<T>> last;
} // DoublyLinkedListNode

template <typename T>
struct BinaryTreeNode : public Node<T> {
    std::unique_ptr<BinaryTreeNode<T>> parent;
    std::unique_ptr<BinaryTreeNode<T>> left;
    std::unique_ptr<BinaryTreeNode<T>> right;
} // class BinaryTreeNode

} // namespace mgg
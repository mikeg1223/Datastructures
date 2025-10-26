#include <memory>

#include "node.h"

namespace mgg{


template<typename T>
class Queue{
public:

    Queue() {
        DoublyLinkedListNode<T> temp = {{nullptr}, nullptr, nullptr};
        _sentinel = std::make_unique<DoublyLinkedListNode<T>>(temp);
        _size = 0;
    }

    Queue(Queue<T>&& other) noexcept = default;

    Queue(Queue<T>& other) = delete;

    void push(std::shared_ptr<T> item){
        DoublyLinkedListNode<T> curr_node = {{item}, nullptr, nullptr};
        std::shared_ptr<DoublyLinkedListNode<T>> curr_node_ptr = std::make_shared<DoublyLinkedListNode<T>>(curr_node);
        if( _size == 0){
            curr_node_ptr->next = nullptr;
            curr_node_ptr->last = nullptr;
            _sentinel->next = curr_node_ptr;
            _sentinel->last = curr_node_ptr;
        } else {
            curr_node_ptr->last = _sentinel->last;
            curr_node_ptr->next = nullptr;
            _sentinel->last->next = curr_node_ptr;
            _sentinel->last = curr_node_ptr;
        }
        _size++;
    }

    void pop(){
        if( _size == 1){
            _sentinel->next = nullptr;
            _sentinel->last = nullptr;
            _size = 0;
        } else if (_size != 0){
            _sentinel->next = _sentinel->next->next;
            _size--;
        }
    }

    std::shared_ptr<T> front(){
        if(_size <= 0){
            throw std::out_of_range("There are no items in the queue");
        }
        return _sentinel->next->data;
    }

    bool contains(std::shared_ptr<T> item){
        // assumes comparable
        if(_size > 0){
            std::shared_ptr<DoublyLinkedListNode<T>> curr = _sentinel->next;
            while(!(*curr->data == *item) && curr->next != nullptr){
                curr = curr->next;
            }
            return *curr->data == *item;
        }
        return false;
    }

    int size(){
        return _size;
    }


private:
    std::unique_ptr<DoublyLinkedListNode<T>> _sentinel;
    int _size;
};


} // namespace mgg
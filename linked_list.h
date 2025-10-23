#pragma once

#include <memory>

#include "node.h"
namespace mgg{

template<typename T>
class LinkedList{
public:
    LinkedList(){
        _head = nullptr;
        _size = 0;
    }

    LinkedList(std::shared_ptr<T> head){
        LinkedListNode<T> temp = {{head}, nullptr};
        _head = std::make_unique<LinkedListNode<T>>(std::move(temp));
        _size = 1;
    }

    LinkedList(const LinkedList<T>& other) = delete;
    LinkedList(LinkedList<T>&& other) noexcept = default;

    void add(std::shared_ptr<T> item){
        if (_head == nullptr){
            LinkedListNode<T> temp = {{item}, nullptr};
            _head = std::make_unique<LinkedListNode<T>>(std::move(temp));
            _size++;
        }
        else {
            auto current = _head.get();
            while(current->next != nullptr){
                current = current->next.get();
            }
            LinkedListNode<T> temp = {{item}, nullptr};
            current->next = std::make_unique<LinkedListNode<T>>(std::move(temp));
            _size++;
        }
    }

    bool contains(std::shared_ptr<T> item){
        if (_head == nullptr){
            return false;
        } else {
            auto current = _head.get();
            if(*current->data == *item) return true; 
            while (current->next != nullptr) {
                current = current->next.get();
                if(*current->data == *item) return true;
            }
        }
        return false;
    }

    void remove(std::shared_ptr<T> item){
        if (_head != nullptr) {
            auto current = _head.get();
            if (*current->data == *item){
                _head = std::move(_head->next);
                return;
            }
            auto last = current;
            while (current->next != nullptr) {
                last = current;
                current = current->next.get();
                if (*current->data == *item){
                    last->next = std::move(current->next);
                    _size--;
                    return;
                }
            }
        }
    }
    
    int size(){
        return _size;
    }

    std::shared_ptr<T> search(std::shared_ptr<T> item){
        if (_head == nullptr) return nullptr;
        if(*_head->data == *item ) return _head->data;
        auto current = _head.get();
        while(current->next != nullptr){
            current = current->next.get();
            if(*current->data == *item){
                return current->data;
            }
        }
        return nullptr;
    }

    LinkedList<T>& operator = (const LinkedList<T>& other) = delete;
    LinkedList<T>& operator = (LinkedList<T>&& other) noexcept = default;

private:
    int _size;
    std::unique_ptr<LinkedListNode<T>> _head;
}; // LinkedList

} // namespace mgg
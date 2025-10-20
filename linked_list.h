#include <memory>
namespace mgg{

namespace {

template <typename T>
struct Node{
    std::unique_ptr<Node<T>> next;
    std::shared_ptr<T> data;
}; // Node

} // namespace

template<typename T>
class LinkedList{
public:
    LinkedList(){
        _head = nullptr;
        _size = 0;
    }

    LinkedList(std::shared_ptr<T> head){
        Node<T> temp = {nullptr, head};
        this->_head = std::make_unique<Node<T>>(temp);
        _size = 1;
    }

    void add(std::shared_ptr<T> item){
        if (_head == nullptr){
            _head = std::make_unique<T>(item);
        }
        else {
            auto current = _head.get();
            while(current->next != nullptr){
                current = current->next.get();
            }
            Node<T> temp = {nullptr, item};
            current.next = std::make_unique<Node<T>>(std::move(temp));
            _size++;
        }
    }

    bool contains(std::shared_ptr<T> item){
        if (_head == nullptr){
            return false;
        } else {
            auto current = _head.get();
            while (current->next != nullptr) {
                if(*current->data == *item) return true;
                current = current->next.get();
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
            while (current.next != nullptr) {
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

private:
    int _size;
    std::unique_ptr<Node<T>> _head;
}; // LinkedList

} // namespace mgg
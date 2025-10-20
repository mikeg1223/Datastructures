#include <memory>
namespace mgg{

template <typename T>
struct Node{
    std::shared_ptr<Node<T>> next;
    std::shared_ptr<T> data;
}; // Node

template<typename T>
class LinkedList{
public:
    LinkedList(){
        head = nullptr;
        size = 0;
    }

    LinkedList(std::shared_ptr<T> head){
        Node<T> temp = {nullptr, head};
        this->head = std::make_unique<Node<T>>(temp);
        size = 1;
    }

    void add(std::shared_ptr<T> item){
        if (head == nullptr){
            head = std::make_unique<T>(item);
        }
        else {
            auto current = *head;
            while(current.next != nullptr){
                current = current.next;
            }
            current.next = item;
            size++;
        }
    }

    bool contains(std::shared_ptr<T> item){
        if (head == nullptr){
            return false;
        } else {
            auto current = *head;
            while (current->next != nullptr) {
                if(*current.data == *item) return true;
                current = *current.next
            }
        }
        return false;
    }

    void remove(std::shared_ptr<T> item){
        if (head != nullptr) {
            auto last = nullptr;
            auto current = *head;
            while (current->next != nullptr) {
                if(*current.data == *item) {
                    last.next = current.next;
                    return;
                };
                last = current;
                current = *current.next
                size--;
            }
        }
    }
    
    int size(){
        return size;
    }

private:
int size;
std::unique_ptr<Node<T>> head;
}; // LinkedList

} // namespace mgg
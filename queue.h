#include <memory>

#include "node.h"

namespace mgg{


template<typename T>
class Queue{
public:

private:
std::unique_ptr<DoublyLinkedListNode<T>> _head;
std::unique_ptr<DoublyLinkedListNode<T>> _tail;
};


} // namespace mgg
#include <memory>
#include <stdexcept>

template<typename T>
class Stack {
public:
    Stack() : _data(std::make_unique<int[]>(16)), _size(0), _storage(16) {}

    Stack(const Stack& other) = delete;
    Stack(Stack&& other) noexcept = default;

    void push(T& item){
        if(_size == _storage){
            expand();
        }
        _data[_size++] = item;
    }

    void pop(){
        if (_size != 0){
            --_size;
        }
    }

    T& top(){
        if(_size == 0){
            throw std::out_of_range("There are no items in the stack");
        }
        return _data[_size];
        
    }

    int size(){
        return _size;
    }

    int storage(){
        return _storage;
    }


private:

    void expand(){
        _storage *= 2;
        std::unique_ptr<T[]> temp = std::make_unique<int[]>(_storage);
        for(int i = 0; i < _size; ++i){
            temp[i] = _data[i];
        }
        _data = std::move(temp);
    }

    std::unique_ptr<T[]> _data;
    int _size;
    int _storage;
};
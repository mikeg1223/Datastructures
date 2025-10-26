#pragma once

#include <memory>
#include <stdexcept>

namespace mgg{

namespace {
    int _MIN_STORAGE = 16;
    int _SHRINKING_FACTOR = 8;
    int _GROWTH_FACTOR = 2;
}

    template<typename T>
class Stack {
public:
    Stack() : _data(std::make_unique<std::shared_ptr<T>[]>(_MIN_STORAGE)), _size(0), _storage(_MIN_STORAGE) {}

    Stack(const Stack& other) = delete;
    Stack(Stack&& other) noexcept = default;

    void push(std::shared_ptr<T> item){
        if(_size == _storage){
            expand();
        }
        _data[_size++] = item;
    }

    void pop(){
        if (_size != 0){
            if(--_size < _storage/_SHRINKING_FACTOR && _storage > _MIN_STORAGE){
                shrink();
            }
        }
    }

    std::shared_ptr<T> top(){
        if(_size == 0){
            throw std::out_of_range("There are no items in the stack");
        }
        return _data[_size-1];
        
    }

    int size(){
        return _size;
    }

    int storage(){
        return _storage;
    }


private:

    void expand(){
        _storage *= _GROWTH_FACTOR;
        std::unique_ptr<std::shared_ptr<T>[]> temp = std::make_unique<std::shared_ptr<T>[]>(_storage);
        for(int i = 0; i < _size; ++i){
            temp[i] = _data[i];
        }
        _data = std::move(temp);
    }

    void shrink(){
        _storage = _storage/ _SHRINKING_FACTOR < _MIN_STORAGE ? _MIN_STORAGE : _storage/ _SHRINKING_FACTOR;
        std::unique_ptr<std::shared_ptr<T>[]> temp = std::make_unique<std::shared_ptr<T>[]>(_storage);
        for(int i = 0; i < _size; ++i){
            temp[i] = _data[i];
        }
        _data = std::move(temp);
    }

    std::unique_ptr<std::shared_ptr<T>[]> _data;
    int _size;
    int _storage;
}; // class Stack

}// namespace mgg
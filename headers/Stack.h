#ifndef STACK_H
#define STACK_H

#include <memory>
#include <exception>
#include <algorithm>

template<class T>
class Stack {
public:
    Stack()
    {
        container = nullptr;
        _size = capacity = 0;
    }

    Stack(Stack&& other)
    {
        capacity = other.capacity;
        _size = other._size;
        container = other.container;
        other.container = nullptr;
    }

    ~Stack() { container = nullptr; }

    class forward_iterator {
    public:
        //The next using's actually make our pointer compatible with pointer templates
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type = T ;
        using pointer    = T*;
        using reference  = T&;

        forward_iterator() { value = nullptr; }
        forward_iterator(pointer arg) { value = arg; }
        ~forward_iterator() { };

        forward_iterator& operator = (pointer arg)
        {
            value = arg;
            return *this;
        }

        forward_iterator& operator ++ ()
        {
            ++value;
            return *this;
        }

        forward_iterator operator ++ (int)
        {
            return value++;
        }

        T& operator *()
        {
            return *value;
        }

        bool operator == (const forward_iterator& other) const
        {
            return value == other.value ? 1 : 0;
        }

        bool operator != (const forward_iterator& other) const
        {
            return value != other.value ? 1 : 0;
        }

        pointer value;
    };

    size_t size(void) const
    {
        return _size;
    }

    bool empty(void) const
    {
        return _size == 0;
    }


    forward_iterator begin(void) const
    {
        return forward_iterator(container.get());
    }

    forward_iterator end(void) const
    {
        return forward_iterator(container.get() + _size);
    }


    Stack& push(T value)
    {
        insert(_size, value);
        return *this;
    }

    Stack& pop(void)
    {
        erase(_size - 1);
        return *this;
    }

    T top(void)
    {
        if (!empty())
            return *(container.get() + _size - 1);
        else throw std::logic_error("Stack is empty");
    }

    void insert(size_t index, T val)
    {
        if (index > _size || index < 0) throw std::logic_error("Outside the bounds");
        if (capacity == _size)
        {
            if (capacity == 0)
            {
                container.reset(new T);
                capacity = 1;
            }
            else 
            {
                capacity *= 2;
                T* temp = new T[capacity];
                std::copy(container.get(), container.get() + _size, temp);
                container.reset(temp);
            }
        }

        for (size_t i = _size; i != index; --i)
            *(container.get() + i) = *(container.get() + i - 1);
        *(container.get() + index) = val;
        ++_size;
    }

    void erase(size_t index)
    {
        if (_size == 0) throw std::logic_error("Stack is empty");
        else if (index >= _size || index < 0) throw std::logic_error("Outside the bounds");
        for (size_t i = index + 1; i != _size; ++i)
            *(container.get() + i - 1) = *(container.get() + i);
        --_size;
    }

    void erase()
    {
        capacity = _size = 0;
        container = nullptr;
    }

private:
    std::shared_ptr<T> container;
    size_t _size, capacity;
};

template<class T>
void swap(Stack<T>& lhs, Stack<T>& rhs)
{
    std::swap(lhs, rhs); //or use std::move semantics
}

#endif

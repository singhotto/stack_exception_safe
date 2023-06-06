#ifndef STACK__HH
#define STACK__HH


#include <cassert>
#include <cstddef>

template <typename T>
class Stack
{
public:
    using size_type = std::size_t;
    explicit Stack(const size_type capacity);
    ~Stack();
    Stack(const Stack &other);
    Stack &operator=(const Stack &other);
    Stack(const Stack &&other);
    Stack &operator=(const Stack &&other);

    size_type size() const;
    void push(const T &elem);
    void pop();
    bool is_empty() const;
    T top();
    bool check_inv() const;

private:
    T *arr;
    size_type size_;
    size_type capacity;

    T& make_copy(const Stack& other);
    T& make_move(const Stack& other);

};

template <typename T>
inline Stack<T>::Stack(const size_type capacity_) : size_(0), capacity(capacity_) {
    if(capacity_ > 0)
        arr = new T[capacity];
    check_inv();
}

template <typename T>
inline Stack<T>::~Stack(){
    delete [] arr;
}

template <typename T>
inline Stack<T>::Stack(const Stack& other){

}


#endif
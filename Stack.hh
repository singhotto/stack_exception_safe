#ifndef STACK__HH
#define STACK__HH

#include <cassert>
#include <cstddef>
#include <string>

template <typename T>
class Stack
{
public:
    using size_type = std::size_t;
    explicit Stack(const size_type capacity = 16);
    ~Stack();
    Stack(const Stack &other);
    Stack &operator=(const Stack &other);
    Stack(Stack &&other) noexcept;
    Stack &operator=(Stack &&other) noexcept;

    int size() const;
    void swap(Stack &other) noexcept;
    void push(const T &elem);
    void pop();
    bool is_empty() const;
    T &top();
    const T &top() const;
    bool check_inv() const;

private:
    T *arr;
    size_type size_;
    size_type capacity;

    static T *make_copy(const T *a, const size_type s, const size_type c);
    static T *make_move(T *a, size_type s, size_type c);
};

template <typename T>
inline Stack<T>::Stack(const size_type capacity_) : size_(0), capacity(capacity_)
{
    if (capacity_ > 0)
        arr = new T[capacity];
    check_inv();
}

template <typename T>
inline Stack<T>::~Stack()
{
    delete[] arr;
}

template <typename T>
inline Stack<T>::Stack(const Stack<T> &other) : arr(make_copy(other.arr, other.size_, other.capacity)), size_(other.size_), capacity(other.capacity) {}

template <typename T>
inline Stack<T> &Stack<T>::operator=(const Stack &other)
{
    Stack temp(other);
    swap(temp);
    return *this;
}

template <typename T>
inline Stack<T>::Stack(Stack<T> &&other) noexcept
{
    assert(other.check_inv());
    swap(std::move(other));
    assert(check_inv());
}

template <typename T>
inline Stack<T> &
Stack<T>::operator=(Stack<T> &&other) noexcept
{
    assert(check_inv() && other.check_inv());
    Stack temp(other);
    swap(temp);
    assert(check_inv());
}

template <typename T>
inline void
Stack<T>::swap(Stack &other) noexcept
{
    using std::swap;
    swap(arr, other.arr);
    swap(size_, other.size_);
    swap(capacity, other.capacity);
}

template <typename T>
inline void
Stack<T>::push(const T &elem)
{
    if (size_ == capacity)
    {
        capacity *= 2;
        T *newArr = make_move(arr, size_, capacity);
        delete[] arr;
        arr = newArr;
    }
    arr[size_++] = elem;
    check_inv();
}

template <typename T>
inline const T &
Stack<T>::top() const
{
    return arr[size_ - 1];
}

template <typename T>
inline T &
Stack<T>::top()
{
    return arr[size_ - 1];
}

template <typename T>
inline void
Stack<T>::pop()
{
    assert(check_inv());
    size_--;
    assert(check_inv());
}

template <typename T>
inline bool
Stack<T>::is_empty() const
{
    assert(check_inv());
    return size_ == 0;
}

template <typename T>
inline int
Stack<T>::size() const
{
    assert(check_inv());
    return size_;
}

template <typename T>
inline bool Stack<T>::check_inv() const
{
    if (capacity == 0 && arr != nullptr)
        return false;
    if (capacity < 0 || arr == nullptr && capacity != 0 || size_ > capacity)
        return false;
    return true;
}

template <typename T>
inline T*
Stack<T>::make_copy(const T *a, const size_type s, const size_type c)
{
    assert(s < c);
    if(c==0)
        return nullptr;
    T* newArr = new T[c];
    try{
        for(size_t i = 0;i<s;i++)
            newArr[i] = a[i];
    }catch(...){
        delete[] newArr;
        throw;
    }
    return newArr;
}

template <typename T>
inline T*
Stack<T>::make_move(T *a, size_type s, size_type c){
    assert(s < c);
    if(c==0)
        return nullptr;
    
    T* newArr = new T[c];
    for(size_t i = 0;i<s;i++)
            newArr[i] = std::move(a[i]);
    return newArr;
}  

#endif
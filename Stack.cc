#include "./Stack.hh"

template <typename T>
bool Stack<T>::check_inv() const
{
    if (capacity == 0 && arr != nullptr)
        return false;
    if (capacity < 0 || arr == nullptr || size_ > capacity)
        return false;
    return true;
}

template <typename T>
T &Stack<T>::make_copy(const Stack &other)
{
    delete arr;
    size_ = other.size();
    arr = new T[size_];
    for (size_t i = 0; i < other.size(); i++)
    {
        arr[i] = other.arr[i];
    }
    return *this;
}
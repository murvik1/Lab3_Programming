#pragma once
#include <cstddef>
#include <iterator>

template <typename T>
class VectorIterator {
private:
    T* ptr_ = nullptr;
public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    using iterator_category =
    std::random_access_iterator_tag;

    VectorIterator() = default;
    explicit VectorIterator(T* ptr) : ptr_(ptr) {}
    reference operator*() const {
         return *ptr_;
    }
    pointer operator->() const { return ptr_;}
    VectorIterator& operator++() {
        ++ptr_;
        return *this;
    }
    VectorIterator operator++(int) { 
        VectorIterator tmp = *this; 
        ++ptr_; 
        return tmp; 
    }
    reference operator[](difference_type n) const { return ptr_[n];}

    VectorIterator& operator--() { --ptr_; return *this; }
    VectorIterator operator--(int) { 
        VectorIterator tmp = *this; 
        --ptr_; 
        return tmp; 
    }

    VectorIterator& operator+=(difference_type n) { ptr_ += n; return *this;}
    VectorIterator& operator-=(difference_type n) { ptr_ -= n; return *this;}
    VectorIterator operator+(difference_type n) const { return VectorIterator(ptr_ + n);}
    VectorIterator operator-(difference_type n) const { return VectorIterator(ptr_ - n);}
    friend VectorIterator operator+(difference_type n, const VectorIterator& it) {
        return it + n;
    }

    difference_type operator-(const VectorIterator& other) const{
        return ptr_ - other.ptr_;
    }

    bool operator==(const VectorIterator& other) const{
        return ptr_ == other.ptr_;
    }
    bool operator<=(const VectorIterator& other) const{
        return ptr_ <= other.ptr_;
    }
    bool operator>=(const VectorIterator& other) const{
        return ptr_ >= other.ptr_;
    }
    bool operator!=(const VectorIterator& other) const{
        return ptr_ != other.ptr_;
    }
    bool operator<(const VectorIterator& other) const{
        return ptr_ < other.ptr_;
    }
    bool operator>(const VectorIterator& other) const{
        return ptr_ > other.ptr_;
    }
};
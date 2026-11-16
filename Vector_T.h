#pragma once
#include <cstddef>
#include <new>    
#include <utility>   
#include <stdexcept>  
#include <concepts>
#include <type_traits>
#include "VectorIterator.h"


template <typename T>
concept Numeric =
 (std::integral<T> || std::floating_point<T>)
 && !std::same_as<T, bool>
 && !std::same_as<T, char>
 && !std::same_as<T, signed char>
 && !std::same_as<T, unsigned char>
 && !std::same_as<T, wchar_t>
 && !std::same_as<T, char8_t>
 && !std::same_as<T, char16_t>
 && !std::same_as<T, char32_t>;
template <Numeric T>
class Vector{
public:
    using iterator = VectorIterator<T>;
    using const_iterator = VectorIterator<const T>;
    using value_type=T;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;
    Vector() = default;
    ~Vector(){
        clear();
        ::operator delete(data_);
    }
    void reserve(size_type new_cap){
        if (new_cap<=capacity_){return;}
        T* new_data = static_cast<T*>(::operator new(new_cap * sizeof(T)));
        for(size_type i = 0; i < size_; i++){
            new(new_data + i) T(std::move(data_[i]));
            data_[i].~T();
        }
        ::operator delete(data_);
        data_=new_data;
        capacity_ = new_cap;
    }
    void clear() {
        for (size_type i = 0; i < size_; ++i)
            data_[i].~T();
        size_ = 0;
    }

    void push_back(const T& value) {
    if (size_ == capacity_) {
        T copy = value;
        reserve(capacity_ + 2); 
        new (data_ + size_) T(copy);
    }
    else{
        new (data_ + size_) T(value);}
    ++size_;
    }

    T pop_back() {
        if (size_ == 0)
            throw std::out_of_range("pop_back on empty Vector");
        size_--;
        T value = std::move(data_[size_]);
        data_[size_].~T();
        return value;
    }
    void resize(size_type new_size){
        if (size_>new_size){
            for(size_type i = new_size; i < size_; i++){
                data_[i].~T();
            }
        }
        else if (new_size>size_){
            reserve(new_size);
            for (size_type i = size_; i < new_size; ++i)
                new (data_ + i) T();

        }
        size_=new_size;
    }
    size_type size() const noexcept {return size_;}
    size_type capacity() const noexcept {return capacity_;}
    bool empty() const noexcept {return size_ == 0;}

    reference operator[](size_type i) {return data_[i];}
    const_reference operator[](size_type i) const {return data_[i];}

    reference at(size_type i) {
        if (i >= size_) {throw std::out_of_range("Vector::at: index out of range");}
        return data_[i];
    }
    const_reference at(size_type i) const {
        if (i >= size_) {throw std::out_of_range("Vector::at: index out of range");}
        return data_[i];
    }

    reference front() {
        if (empty()) throw std::out_of_range("Vector::front: vector is empty");
        return data_[0];
    }
    const_reference front() const {
        if (empty()) throw std::out_of_range("Vector::front: vector is empty");
        return data_[0];
    }
    reference back() {
        if (empty()) throw std::out_of_range("Vector::back: vector is empty");
        return data_[size_ - 1];
    }
    const_reference back() const {
        if (empty()) throw std::out_of_range("Vector::back: vector is empty");
        return data_[size_ - 1];
    }

    Vector(const Vector& other){
        reserve(other.size_);
        for (size_type i = 0; i < other.size_; ++i)
            new (data_ + i) T(other.data_[i]);
        size_ = other.size_;
    }

    Vector(Vector&& other)
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector tmp(other);
            swap(tmp);
        }
        return *this;
    }

    void swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            clear();
            ::operator delete(data_);
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }
    iterator begin(){
        return iterator(data_);
    }
    iterator end(){
        return iterator(data_ + size_);
    }
    const_iterator begin() const { 
        return const_iterator(data_);
    }
    const_iterator end() const {
        return const_iterator(data_ + size_);
    }
private:
    T* data_ = nullptr;
    size_type size_ = 0;
    size_type capacity_ = 0; 



};





#pragma once
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

//Shoutout to these guys for ideas on circular buffer logic: https://www.geeksforgeeks.org/cpp/implement-circular-buffer-using-std-vector-in-cpp/
template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() : capacity_(4), size_(0), front_(0), back_(0), data_(new T[capacity_]) {}
    explicit ABDQ(std::size_t capacity) : capacity_(capacity), size_(0), front_(0), back_(0), data_(new T[capacity]) {}
    
    ABDQ(const ABDQ& other) : capacity_(other.capacity_), size_(other.size_), front_(0), back_(size_), data_(new T[other.capacity_]) {
        for(size_t i = 0; i < size_; i++){
            data_[i] = other.data_[(other.front_+i) % other.capacity_];
        }
    }
    ABDQ(ABDQ&& other) noexcept : capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_), data_(other.data_){
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.size_ = 0;
    }
    ABDQ& operator=(const ABDQ& other){
        if(this != &other){
            delete[] data_;
            data_ = new T[other.capacity_];
            capacity_ = other.capacity_;
            front_ = 0;
            back_ = other.size_;
            size_ = other.size_;

            for(size_t i = 0; i < other.size_; i++){
                data_[i] = other.data_[(other.front_ + i) % other.capacity_];
            }
            
        }
        return *this;
    }

    ABDQ& operator=(ABDQ&& other) noexcept {
        if(this != &other){
            delete[] data_;
            data_ = other.data_;
            capacity_ = other.capacity_;
            front_ = other.front_;
            back_ = other.back_;
            size_ = other.size_;
            
            other.data_ = nullptr;
            other.capacity_ = 0;
            other.front_ = 0;
            other.back_ = 0; 
            other.size_ = 0;
        }
        return *this;
    } 

    ~ABDQ() override {delete[] data_;}

    // Insertion
    void pushFront(const T& item) override {
        ensureCapacity();
        front_ = ((capacity_ - 1) + front_) % capacity_;
        data_[front_] = item;
        size_++;
    }
    void pushBack(const T& item) override {
       ensureCapacity();
       data_[back_] = item;
       back_ = (back_ + 1) % capacity_;
       size_++; 
    }

    // Deletion
    T popFront() override {
        if(size_ == 0) {throw std::runtime_error("Deque empty");}
        T val = data_[front_];
        front_ = (front_+1) % capacity_;
        size_--;
        shrinkIfNeeded();
        return val;
    }

    T popBack() override {
        if(size_ == 0) {throw std::runtime_error("Deque empty");}
        back_ = (((capacity_ - 1) + back_) % capacity_);
        T val = data_[back_];
        size_--;
        shrinkIfNeeded();
        return val;
    }

    // Access
    const T& front() const override {
        if(size_ == 0) {throw std::runtime_error("Deque empty");}
        return data_[front_];
    }
    const T& back() const override {
        if(size_ == 0) {throw std::runtime_error("Deque empty");}
        return data_[((capacity_ -1 )+ back_) % capacity_];
    }

    // Getters
    std::size_t getSize() const noexcept override {return size_;}

    void ensureCapacity() { 
        if(size_ == capacity_ ){
            size_t newcap = capacity_ * SCALE_FACTOR;
            T* novdata_ = new T[newcap];
            for(size_t i = 0; i<size_; i++){
                novdata_[i] = data_[(front_+i)%capacity_];
            }
            delete[] data_;
            data_ = novdata_;
            capacity_ = newcap;
            front_ = 0;
            back_ = size_;
        }
    }
    void shrinkIfNeeded() {
        if(size_ <= capacity_ / 4 && capacity_ > 4){
            size_t newcap = capacity_/2;
            if(newcap < 4) {newcap = 4;}
            T* novdata_ = new T[newcap];

            for(size_t i = 0; i < size_; i++){
                novdata_[i] = data_[(front_+i)%capacity_];
            }

            delete[] data_;
            data_ = novdata_;
            capacity_ = newcap;
            front_ = 0;
            back_ = size_;
        }
    }

    void PrintForward() const {
        for(size_t i = 0; i < size_; i++){
            std::cout << data_[(front_ +i) % capacity_] << '\n';
        }
    }

    void PrintReverse() const {
        for(int i = 0; i < size_; i++){
            std::cout << data_[(back_ + capacity_-i-1) % capacity_ ] << '\n';
        }
    }

};

#pragma once
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ() : capacity_(1), curr_size_(0), array_(new T[capacity_]) {}
    
    explicit ABQ(const size_t capacity) : capacity_(capacity), curr_size_(0), array_(new T[capacity_]) {}
    
    ABQ(const ABQ& other) : capacity_(other.capacity_), curr_size_(other.curr_size_) {
        array_ = new T[other.capacity_];
        for(size_t i = 0; i < other.curr_size_; i++){
            array_[i] = other.array_[i];
        }
    }
    ABQ& operator=(const ABQ& rhs) {
        if(this != &rhs ){
            delete[] array_;
            array_ = new T[rhs.capacity_];
            for(size_t i = 0; i < rhs.curr_size_; i++){
                array_[i] = rhs.array_[i];
            }   
            curr_size_ = rhs.curr_size_;
            capacity_ = rhs.capacity_;
        }
        return *this;
    }

    ABQ(ABQ&& other) noexcept : capacity_(other.capacity_), curr_size_(other.curr_size_) {
        array_ = other.array_;

        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
    }

    ABQ& operator=(ABQ&& rhs) noexcept {
        if(this != &rhs){
            delete[] array_;
            array_ = rhs.array_;
            capacity_ = rhs.capacity_;
            curr_size_ = rhs.curr_size_;    

            rhs.array_ = nullptr;
            rhs.capacity_ = 0;
            rhs.curr_size_ = 0;
        }
        return *this;
    }
    ~ABQ() noexcept override {
        delete[] array_;
    }

    void printForward() const {
        for(size_t i = 0; i < curr_size_; i++){
            std::cout << array_[i] << '\n';
        }
    }

    void printReverse() const {
        for(int i = static_cast<int>(curr_size_)-1; i >= 0; i--){
            std::cout << array_[i] << '\n';
        }
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override {return curr_size_;}
    [[nodiscard]] size_t getMaxCapacity() const noexcept {return capacity_;}
    [[nodiscard]] T* getData() const noexcept {return array_;}

    // Insertion
    void enqueue(const T& data) override {
        if(curr_size_ == capacity_){
            capacity_ *= scale_factor_;
            T* novarray_ = new T[capacity_];
            for(size_t i = 0; i < curr_size_; i++)
            {
                novarray_[i] = array_[i];
            }
            delete[] array_;
            array_ = novarray_;

        }

        array_[curr_size_] = data;
        curr_size_++;
    }

    // Access
    T peek() const override {
        if(curr_size_ == 0){throw std::runtime_error("empty"); }
        return array_[0];
    }

    // Deletion
    T dequeue() override {
        if(curr_size_ == 0){throw std::runtime_error("empty"); }
        T value = array_[0];

        for (size_t i = 1; i < curr_size_; i++){
            array_[i - 1] = array_[i];
        }

        if(curr_size_ <= capacity_ /4 && capacity_ > 1){
            size_t newcap = capacity_/scale_factor_;
            if(newcap < 1) {newcap = 1;}
            T* novarray_ = new T[newcap];
            for(size_t i = 0; i<curr_size_; i++){
                novarray_[i] = array_[i];
            }
            delete[] array_;
            array_ = novarray_;
            capacity_ = newcap;
        }

        return value; 

        curr_size_--;
        return value; 
    }

};

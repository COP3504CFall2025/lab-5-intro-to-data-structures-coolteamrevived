#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ();

    // Core Insertion Operations
    void pushFront(const T& item) override {list.addHead(item);}
    void pushBack(const T& item) override {list.addTail(item);}

    // Core Removal Operations
    T popFront() override {
        if(list.getCount() == 0) {throw std::out_of_range("Deque empty");}
        T val = (list.getHead())->data;
        list.removeHead();
        return val;
    }
    T popBack() override {
        if(list.getCount() == 0) {throw std::out_of_range("Deque empty");}
        T val = (list.getTail())->data;
        list.removeTail();
        return val;
    }

    // Element Accessors
    const T& front() const override {
        if(list.getCount() == 0) {throw std::out_of_range("Deque empty");}
        return(list.getHead())->data;}
    const T& back() const override {
        if(list.getCount() == 0) {throw std::out_of_range("Deque empty");}
        return(list.getTail())->data;}

    void PrintForward() const {
        list.PrintForward();
    }

    void PrintReverse() const {
        list.PrintReverse();
    }

    // Getter
    std::size_t getSize() const noexcept override {return static_cast<size_t>(list.getCount());}
};







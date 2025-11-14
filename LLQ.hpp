#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ(): list() {}

    void printForward() const {
        list.PrintForward();
    }

    void printReverse() const {
        list.printReverse();
    }

    // Insertion
    void enqueue(const T& item) override {list.addTail(item);}

    // Deletion
    T dequeue() override {
        if(list.getCount() == 0) {throw std::runtime_error("Queue empty");}
        T val = (list.getHead())->data;
        list.removeHead();
        return val;
    }

    // Access
    T peek() const override {
        if(list.getCount() == 0) {throw std::runtime_error("Queue empty");}
        return ((list.getHead())->data);
    }

    // Getter
    std::size_t getSize() const noexcept override {return static_cast<size_t>(list.getCount());}

};
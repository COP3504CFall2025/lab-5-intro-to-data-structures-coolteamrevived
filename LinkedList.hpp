#pragma once
#include <iostream>
using namespace std;



template <typename T>
class LinkedList {
public:
	struct Node {
		T data;
		Node* prev;
		Node* next;
		Node(const T& value, Node* prev = nullptr, Node* next = nullptr ) : data(value), prev(prev), next(next) {}
	};
	
	// Behaviors
	void printForward() const {
		if(count == 0) {return;}
		Node* cnodp = head;
		while(cnodp->next != nullptr){
			std::cout << cnodp->data << '\n';
			cnodp = cnodp->next;
		}
		std::cout << cnodp->data << '\n';

		
	}
	void printReverse() const {
		if(count == 0) {return;}
		Node* cnodp = tail;
		while(cnodp->prev != nullptr){
			std::cout << cnodp->data << '\n';
			cnodp = cnodp->prev;
		}
		std::cout << cnodp->data << '\n';

	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {return count;}
	Node* getHead() {return head;}
	const Node* getHead() const {return head;}
	Node* getTail() {return tail;}
	const Node* getTail() const {return tail;}

	// Insertion
	void addHead(const T& data) {
		Node* newHead = new Node(data, nullptr, head);
		if(head == nullptr){head = newHead; tail = newHead;}
		else{head->prev = newHead; head = head->prev;}
		
		count++;
	}
	void addTail(const T& data) {
		Node* newTail = new Node(data, tail, nullptr);
		if(tail == nullptr){head = newTail; tail = newTail;}
		else{tail->next = newTail; tail = tail->next;}
		
		count++;
	}

	// Removal
	bool removeHead() {
		if(head == nullptr) {return false;}
		Node* t  = head;
		if(count == 1) {head = nullptr; tail = nullptr;}
		else
		{
			head = head->next;
			head->prev = nullptr;
		}
		delete t;
		t = nullptr;
		count--;
		return true;
	}
	
	bool removeTail() {
		if(head == nullptr) {return false;}
		Node* t  = tail;
		if(count == 1) {head = nullptr; tail = nullptr;}
		else
		{
			tail = tail->prev;
			tail->next = nullptr;
		}
		delete t;
		t = nullptr;
		count--;
		return true;
	}
	void clear() {
		if(count == 0) {return;}
		Node* cnodp = head;
		while(cnodp!= nullptr){
			Node* n = cnodp->next;
			delete cnodp;
			cnodp = n;
		}
		count = 0;
		head = nullptr;
		tail = nullptr;
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if(this != &other){
			clear();
			head = other.head;
			tail = other.tail;
			count = other.count;

			other.head = nullptr;
			other.tail = nullptr;
			other.count = 0;
		}
		return *this;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs){
		if(this != &rhs){
			clear();
			Node* cnodp = rhs.head;
			while(cnodp != nullptr) {
				addTail(cnodp->data);
				cnodp = cnodp->next;
			}
		}
		return *this;
	}

	// Construction/Destruction
	LinkedList() : head(nullptr), tail(nullptr), count(0) {}

	LinkedList(const LinkedList<T>& list) : head(nullptr), tail(nullptr), count(0) {
		Node* cnodp = list.head;
		while(cnodp != nullptr){
			addTail(cnodp->data);
			cnodp = cnodp->next;
		} 
	}
	LinkedList(LinkedList<T>&& other) noexcept : head(other.head), tail(other.tail), count(other.count) {
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;

	}
	~LinkedList() {clear();}

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;
};



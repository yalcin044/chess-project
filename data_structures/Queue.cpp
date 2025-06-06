#include "Queue.hpp"

Queue::Queue() : front(nullptr), back(nullptr), size(0) { }

Queue::~Queue() {
    clear();
}

bool Queue::isEmpty() const {
    return front == nullptr;
}

void Queue::enqueue(const std::string& newItem) { 
    Node *newNode = new Node;
    newNode -> data = newItem;
    newNode -> next = nullptr; 
    
    if (isEmpty()){
        front = newNode;
        back = newNode;
    }
    else {
        back -> next = newNode;
        back = newNode;
    }
    size++; 
}

void Queue::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    
    Node *temp = front;
    front = front -> next;
    temp -> next = nullptr;
    delete temp;
    size--;

    if (isEmpty()){
        back = nullptr;
    }
}

std::string& Queue::getFront() { 
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    
    return front -> data;
}

int Queue::getSize() const {
    return size;
}

void Queue::clear() {
    while (!isEmpty()) {
        dequeue();
    }
}

void Queue::enterCooldownQueue(const std::string& portalId) { 
    enqueue(portalId);
}


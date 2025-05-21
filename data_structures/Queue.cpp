#include "Queue.hpp"

//Initialize the queue
Queue::Queue() : front(nullptr), back(nullptr), size(0) { }

//Check wheter the queue is empty
bool Queue::isEmpty() const {
    return front == nullptr;
}

//Add item back to the queue
void Queue::enqueue(const int& newItem) {
    Node *newNode = new Node;
    newNode -> data = newItem;
    
    if (isEmpty()){
        front = newNode;
        back = newNode;
    }
    else {
        back -> next = newNode;
        back = newNode;
    }
}

//Remove the front node from the queue

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

//Retrieve the front data from the queue

int& Queue::getFront() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    
    return front -> data;
}

//Return the size of the queue

int Queue::getSize() const {
    return size;
}

//Add a portal into the cooldown queue when used

void Queue::enterCooldownQueue(const int& cooldownPortal) {
    enqueue(cooldownPortal);
}

//Check all portals' cooldown and decrement 1
//if cooldown eaquals to the zero after decrement remove from the queue
//else add into the back of queue
/*
void Queue::checkCooldowns() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    
    int checkSize = getSize();
    
    for (int check = 0; check < checkSize; check++) {
        int& currentPortal = getFront();
        currentPortal.cooldown--;

        if (currentPortal.cooldown != 0) 
            enqueue(currentPortal);
        
        dequeue();
    }
}
*/
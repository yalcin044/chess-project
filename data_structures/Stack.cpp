#include "Stack.hpp"

//Initialize the stack

Stack::Stack() : top(nullptr), size(0) { }

//Check wheter the stack is empty
bool Stack::isEmpty() const {
    return top == nullptr;
}

//Add item top to the stack
void Stack::push(const int& newItem) {
    Node *newNode = new Node;
    newNode -> data = newItem;
    newNode -> next = top;
    top = newNode;
    size++;
}

//Remove the top node from the stack
void Stack::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }

    Node *temp = top;
    top = top -> next;
    temp -> next = nullptr;
    delete temp;
    size--;
}

//Retrieve the top data from the stack
int& Stack::getTop() {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }

    return top -> data;
}

//Return the size of the stack
int Stack::getSize() const {
    return size;
}

//Save the last move into the stack
void Stack::moveRecord(const int& record) {
    push(record);
}

//Undo the last move and remove from the stack
int Stack::moveUndo() {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }

    int lastMove = getTop();
    pop();
    return lastMove;
}

//Retrieve the last move from the stack
int& Stack::getLastMove() {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }

    return getTop();
}
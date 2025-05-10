#include "Stack.hpp"

//Initialize the stack
template<class ItemType>
Stack<ItemType>::Stack() : top(nullptr), size(0) { }

//Check wheter the stack is empty
template<class ItemType>
bool Stack<ItemType>::isEmpty() const {
    return top == nullptr;
}

//Add item top to the stack
template<class ItemType>
void Stack<ItemType>::push(const ItemType& newItem) {
    Node *newNode = new Node;
    newNode -> data = newItem;
    newNode -> next = top;
    top = newNode;
    size++;
}

//Remove the top node from the stack
template<class ItemType>
void Stack<ItemType>::pop() {
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
template<class ItemType>
ItemType& Stack<ItemType>::getTop() {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }

    return top -> data;
}

//Return the size of the stack
template<class ItemType>
int Stack<ItemType>::getSize() const {
    return size;
}

//Save the last move into the stack
template<class ItemType>
void Stack<ItemType>::moveRecord(const ItemType& record) {
    push(record);
}

//Undo the last move and remove from the stack
template<class ItemType>
ItemType Stack<ItemType>::moveUndo() {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }

    ItemType lastMove = getTop();
    pop();
    return lastMove;
}

//Retrieve the last move from the stack
template<class ItemType>
ItemType& Stack<ItemType>::getLastMove() {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }

    return getTop();
}
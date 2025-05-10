#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>

template<class ItemType>
class Stack{
    public:
        //Stack constructor
        Stack();

        //Standart stack operations
        bool isEmpty() const;
        void push(const ItemType& newItem);
        void pop();
        ItemType& getTop();
        int getSize() const;
        void clear();

        //Some move operations for the chess pieces
        void moveRecord(const ItemType& record);
        ItemType moveUndo();
        ItemType& getLastMove();

    private:
        struct Node{
            Node *next;
            ItemType data;
        };
        
        Node *top;   
        int size;
};

#endif 
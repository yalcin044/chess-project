#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>


class Stack{
    public:
        //Stack constructor
        Stack();

        //Standart stack operations
        bool isEmpty() const;
        void push(const int& newItem);
        void pop();
        int& getTop();
        int getSize() const;
        void clear();

        //Some move operations for the chess pieces
        void moveRecord(const int& record);
        int moveUndo();
        int& getLastMove();

    private:
        struct Node{
            Node *next;
            int data;
        };
        
        Node *top;   
        int size;
};

#endif 
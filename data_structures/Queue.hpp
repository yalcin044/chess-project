#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>

class Queue {
    public:
        //Queue constructor
        Queue();
        
        //Standart queue operations 
        bool isEmpty() const;
        void enqueue(const int& newItem);
        void dequeue();
        int& getFront();
        int getSize() const;
        void clear();

        //Some cooldown operations for portals
        void enterCooldownQueue(const int& cooldownPortal);
        //void checkCooldowns();
    
    private:
        struct Node {
            Node *next;
            int data;
        };
        
        Node *front;
        Node *back;
        int size;
};

#endif
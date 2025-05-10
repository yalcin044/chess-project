#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>

template<class ItemType>
class Queue {
    public:
        //Queue constructor
        Queue();
        
        //Standart queue operations 
        bool isEmpty() const;
        void enqueue(const ItemType& newItem);
        void dequeue();
        ItemType& getFront() ;
        int getSize() const;
        void clear();

        //Some cooldown operations for portals
        void enterCooldownQueue(const ItemType& cooldownPortal);
        void checkCooldowns();
    
    private:
        struct Node {
            Node *next;
            ItemType data;
        };
        
        Node *front;
        Node *back;
        int size;
};

#endif
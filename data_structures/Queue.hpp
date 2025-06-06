#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <string> 

class Queue {
    public:
        Queue();
        ~Queue(); 
        bool isEmpty() const;
        void enqueue(const std::string& newItem);
        void dequeue();
        std::string& getFront(); 
        int getSize() const;
        void clear();
        void enterCooldownQueue(const std::string& portalId);
       
    
    private:
        struct Node {
            Node *next;
            std::string data; 
        };
        
        Node *front;
        Node *back;
        int size;
};

#endif
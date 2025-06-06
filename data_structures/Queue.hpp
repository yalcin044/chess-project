#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <string> // newItem std::string olacağı için

class Queue {
    public:
        Queue();
        ~Queue(); // Yıkıcı ekle

        bool isEmpty() const;
        void enqueue(const std::string& newItem); // int yerine std::string alacak
        void dequeue();
        std::string& getFront(); // int& yerine std::string& döndürecek
        int getSize() const;
        void clear();

        // Portal işlemleri için, bu metot sadece portal ID'sini kaydeder.
        // Cooldown mantığı PortalSystem'de yönetilecektir.
        void enterCooldownQueue(const std::string& portalId); // int yerine std::string alacak
        // void checkCooldowns(); // Bu metodu Queue'dan tamamen kaldırıyoruz, PortalSystem yönetecek
    
    private:
        struct Node {
            Node *next;
            std::string data; // int yerine std::string tutacak
        };
        
        Node *front;
        Node *back;
        int size;
};

#endif
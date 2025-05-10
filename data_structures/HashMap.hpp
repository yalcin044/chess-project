#ifndef HASHMAP_HPP
#define HASHMAP_HPP


#include <iostream>
#include <map>
#include <string>
#include <vector>

template<class ItemType>
class HashMap{
    public:
        HashMap();

        ItemType getPiece(const std::string position);
        void placePiece(const std::string position, const ItemType piece);
        void removePiece(const std::string position);



    private:
        struct Piece{
            int x;
            int y;
            std::string color;
            std::string type;
        };
        
        std::vector<std::vector<std::string>> positions;
        std::map<String, ItemType> board;
};


#endif //HASHMAP_HPP
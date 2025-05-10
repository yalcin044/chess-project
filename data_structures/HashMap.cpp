#include "HashMap.hpp"

template<class ItemType>
HashMap<class ItemType>::HashMap() { };


template<class ItemType>
ItemType HashMap<class ItemType>::getPiece(const std::string position){
    return board.find(position);
}

template<class ItemType>
void HashMap<class ItemType>::placePiece(const std::string position, const ItemType piece){
    board[position] = piece;
}

template<class ItemType>
void HashMap<class ItemType>::removePiece(const std::string position){
    board[position] = 0;
}
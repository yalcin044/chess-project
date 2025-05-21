#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "Pieces.hpp" 
#include "../include/ConfigReader.hpp"
#include "../chess_board/ChessBoard.hpp"
#include <iostream>
#include <string>       // Temel Piece sınıfını dahil et

// Piyon sınıfı, Piece sınıfından türetilmiştir.
class Bishop : public Pieces {
public:
    // Piyonun kurucu fonksiyonu.
    Bishop(const std::string& color, const Movement& movement, const SpecialAbilities& special_abilities);
    
    /*
    // Piece sınıfındaki pure virtual metodları override eder ve kendi implementasyonlarını bildirir.
    std::vector<Position> getPossibleMoves(const ChessBoard& board) const override;
    bool isValidMove(const Position& start, const Position& end, const ChessBoard& board) const override;
    */
};

#endif // BISHOP_HPP
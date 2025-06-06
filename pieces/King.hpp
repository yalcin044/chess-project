#ifndef KING_HPP
#define KING_HPP

#include "Pieces.hpp" 
#include "../include/ConfigReader.hpp"
#include "../chess_board/ChessBoard.hpp"
#include <iostream>
#include <string>       

class King : public Pieces {
public:
    King(const std::string& color, const Movement& movement, const SpecialAbilities& special_abilities);

    std::vector<Position> getPossibleMoves(const ChessBoard& board) const override;
    bool isValidMove(const Position& start, const Position& end, const ChessBoard& board) const override;
};

#endif // KING_HPP
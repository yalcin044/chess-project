#include "King.hpp" 
#include "Pieces.hpp" 
#include "../chess_board/ChessBoard.hpp" 
#include <cmath> 

King::King(const std::string& color, const Movement& movement, const SpecialAbilities& special_abilities)
    : Pieces("King", color, movement, special_abilities) {} 

std::vector<Position> King::getPossibleMoves(const ChessBoard& board) const {
    std::vector<Position> possible_moves;

    int directions[8][2] = {
        {0, 1}, {0, -1}, {-1, 0}, {1, 0},   
        {-1, 1}, {1, 1}, {-1, -1}, {1, -1} 
    };

    for (int i = 0; i < 8; ++i) {
        int dx = directions[i][0]; 
        int dy = directions[i][1]; 

        Position next_pos = {m_current_position.x + dx, m_current_position.y + dy}; 

        if (board.checkBoundCorrect(next_pos)) {
            Pieces* target_piece = board.getPiece(next_pos); 

            if (target_piece == nullptr || target_piece->getColor() != m_color) {
                possible_moves.push_back(next_pos); 
            }
        }
    }

    return possible_moves;
}

bool King::isValidMove(const Position& start, const Position& end, const ChessBoard& board) const {
    if (start.x == end.x && start.y == end.y) {
        return false;
    }

    if (!board.checkBoundCorrect(end)) {
        return false;
    }

    int dx = std::abs(end.x - start.x); 
    int dy = std::abs(end.y - start.y); 

    if (dx > 1 || dy > 1) {
        return false;
    }

    bool is_horizontal_or_vertical = (dx == 0 && dy == 1) || (dx == 1 && dy == 0);
    bool is_diagonal = (dx == 1 && dy == 1);

    if (!(is_horizontal_or_vertical || is_diagonal)) {
        return false; 
    }

    Pieces* target_piece = board.getPiece(end);
    if (target_piece == nullptr) { 
        return true; 
    }
    else {
        return target_piece->getColor() != m_color; 
    }
}
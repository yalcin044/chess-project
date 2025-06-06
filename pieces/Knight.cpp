#include "Knight.hpp" 
#include "Pieces.hpp"
#include "../chess_board/ChessBoard.hpp" 
#include <cmath> 

Knight::Knight(const std::string& color, const Movement& movement, const SpecialAbilities& special_abilities)
    : Pieces("Knight", color, movement, special_abilities) {}

std::vector<Position> Knight::getPossibleMoves(const ChessBoard& board) const {
    std::vector<Position> possible_moves;

    int directions[8][2] = {
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}, 
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1}  
    };

    if (!m_movement_rules.l_shape) {
        return possible_moves; 
    }

    for (int i = 0; i < 8; ++i) {
        Position next_pos = {m_current_position.x + directions[i][0], m_current_position.y + directions[i][1]};


        if (board.checkBoundCorrect(next_pos)) {
            Pieces* target_piece = board.getPiece(next_pos);

            if (target_piece == nullptr || target_piece->getColor() != m_color) {
                possible_moves.push_back(next_pos); 
            }
        }
    }
    return possible_moves;
}

bool Knight::isValidMove(const Position& start, const Position& end, const ChessBoard& board) const {
    if (start.x == end.x && start.y == end.y) {
        return false;
    }

    if (!board.checkBoundCorrect(end)) {
        return false;
    }

    if (!m_movement_rules.l_shape) {
        return false;
    }

    int dx = std::abs(end.x - start.x); 
    int dy = std::abs(end.y - start.y); 

    bool is_l_shape_move = (dx == 1 && dy == 2) || (dx == 2 && dy == 1);
    if (!is_l_shape_move) {
        return false;
    }

    Pieces* target_piece = board.getPiece(end);
    if (target_piece == nullptr) { 
        return true; 
    } else { 
        return target_piece->getColor() != m_color; 
    }
}
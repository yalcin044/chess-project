#include "Bishop.hpp" 
#include "Pieces.hpp" 
#include "../chess_board/ChessBoard.hpp" 
#include <cmath> 

Bishop::Bishop(const std::string& color, const Movement& movement, const SpecialAbilities& special_abilities)
    : Pieces("Bishop", color, movement, special_abilities) {} 

std::vector<Position> Bishop::getPossibleMoves(const ChessBoard& board) const {
    std::vector<Position> possible_moves;
    int directions[4][2] = {
        {-1, 1}, {1, 1}, {-1, -1}, {1, -1} 
    };

    int max_distance = m_movement_rules.diagonal;
    if (max_distance == 0) {
        return possible_moves; 
    }

    for (int i = 0; i < 4; ++i) { 
        int dx = directions[i][0]; 
        int dy = directions[i][1]; 

        for (int step = 1; step <= max_distance; ++step) {
            Position next_pos = {m_current_position.x + dx * step, m_current_position.y + dy * step};

            if (!board.checkBoundCorrect(next_pos)) {
                break;
            }

            Pieces* target_piece = board.getPiece(next_pos);

            if (target_piece == nullptr) { 
                possible_moves.push_back(next_pos); 
            } else { 
                if (target_piece->getColor() != m_color) { 
                    possible_moves.push_back(next_pos); 
                }

                break;
            }
        }
    }
    return possible_moves; 
}

bool Bishop::isValidMove(const Position& start, const Position& end, const ChessBoard& board) const {
    if (start.x == end.x && start.y == end.y) {
        return false;
    }

    if (!board.checkBoundCorrect(end)) {
        return false;
    }

    int dx = end.x - start.x; 
    int dy = end.y - start.y; 

    if (std::abs(dx) != std::abs(dy) || dx == 0) { 
        return false;
    }

    if (m_movement_rules.diagonal == 0) {
        return false;
    }

    int step_x;
    if (dx > 0) {
        step_x = 1;
    } else { 
        step_x = -1;
    }

    int step_y;
    if (dy > 0) {
        step_y = 1;
    } else { 
        step_y = -1;
    }

  
    int steps = std::abs(dx); 
    for (int i = 1; i < steps; ++i) { 
        Position intermediate_pos = {start.x + i * step_x, start.y + i * step_y};
        if (board.getPiece(intermediate_pos) != nullptr) {
            return false; 
        }
    }

    Pieces* target_piece = board.getPiece(end);
    if (target_piece == nullptr) { 
        return true; 
    } else { 
        return target_piece->getColor() != m_color;
    }
}
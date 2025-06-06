#include "Pawn.hpp"    
#include "Pieces.hpp"   
#include "../chess_board/ChessBoard.hpp"
#include <cmath>        

Pawn::Pawn(const std::string& color, const Movement& movement, const SpecialAbilities& special_abilities)
    : Pieces("Pawn", color, movement, special_abilities) {}

std::vector<Position> Pawn::getPossibleMoves(const ChessBoard& board) const {
    std::vector<Position> possible_moves;
    int directions;
    if (m_color == "white") directions = 1;
    else directions = -1;

  
    Position next_pos_forward;
    next_pos_forward = {
        m_current_position.x, 
        m_current_position.y + directions
    };
    
 
    if (m_movement_rules.forward >= 1 && 
        board.checkBoundCorrect(next_pos_forward) && 
        board.getPiece(next_pos_forward) == nullptr) {
        possible_moves.push_back(next_pos_forward);
    }

    if (!m_has_moved && m_movement_rules.first_move_forward >= 2) {
        Position double_step_pos;
        double_step_pos = {
            m_current_position.x, 
            m_current_position.y + 2 * directions
        };
        
        Position intermediate_pos; 
        intermediate_pos = {
            m_current_position.x, 
            m_current_position.y + directions
        }; 
        
        
        if (board.checkBoundCorrect(double_step_pos) && 
        board.getPiece(double_step_pos) == nullptr && 
        board.getPiece(intermediate_pos) == nullptr) {
            possible_moves.push_back(double_step_pos);
        }
    }


    if (m_movement_rules.diagonal_capture >= 1) {
        Position capture_left;
        capture_left = {
            m_current_position.x - 1, 
            m_current_position.y + directions
        };
        
        Position capture_right;
        capture_right = {
            m_current_position.x + 1, 
            m_current_position.y + directions
        };

        Pieces* target_left = board.getPiece(capture_left);
        if (board.checkBoundCorrect(capture_left) && 
        target_left != nullptr && 
        target_left -> getColor() != m_color) {
            possible_moves.push_back(capture_left);
        }

        Pieces* target_right = board.getPiece(capture_right);
        if (board.checkBoundCorrect(capture_right) && 
        target_right != nullptr && 
        target_right -> getColor() != m_color) {
            possible_moves.push_back(capture_right);
        }
    }

    return possible_moves;
}

bool Pawn::isValidMove(const Position& start, const Position& end, const ChessBoard& board) const {
    if (start.x == end.x && start.y == end.y) return false;
    if (!board.checkBoundCorrect(end)) return false;

    int dx = end.x - start.x;
    int dy = end.y - start.y;
    int direction = (m_color == "white") ? 1 : -1;

    Pieces* target_piece = board.getPiece(end);

    if (dx == 0 && dy == direction) {
        return target_piece == nullptr; 
    }

    if (!m_has_moved && dx == 0 && dy == 2 * direction && m_movement_rules.first_move_forward >= 2) {
        Position intermediate_pos;
        intermediate_pos = {
            start.x,
            start.y + direction
        };
        return target_piece == nullptr && board.getPiece(intermediate_pos) == nullptr;
    }

    if (m_movement_rules.diagonal_capture >= 1 && std::abs(dx) == 1 && dy == direction) {
        return target_piece != nullptr && target_piece -> getColor() != m_color; 
    }

    return false;
}

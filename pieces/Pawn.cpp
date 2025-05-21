#include "Pawn.hpp"     // Kendi başlık dosyasını dahil et
#include "Pieces.hpp"   // ChessBoard'a erişim için (getPieceAt, isWithinBounds)
#include "../chess_board/ChessBoard.hpp"
#include <cmath>        // std::abs için
                
// Pawn sınıfının kurucu fonksiyonu implementasyonu
// Temel Piece sınıfının kurucusunu çağırır ve taşın tipini "Pawn" olarak ayarlar.
Pawn::Pawn(const std::string& color, const Movement& movement, const SpecialAbilities& special_abilities)
    : Pieces("Pawn", color, movement, special_abilities) {}

// Piyonun olası hamlelerini hesaplayan implementasyon

/*
std::vector<Position> Pawn::getPossibleMoves(const ChessBoard& board) const {
    std::vector<Position> possible_moves;
    int direction = (m_color == "white") ? 1 : -1; // Beyaz piyonlar ileri (+Y), siyahlar geri (-Y)

    // Normal ileri hareket (1 kare)
    Position next_pos_forward;
    next_pos_forward = {
        m_current_position.x, 
        m_current_position.y + direction
    };
    
    // JSON'dan gelen `forward` kuralı kontrol edilir.
    if (m_movement_rules.forward >= 1 && 
        board.checkBoundCorrect(next_pos_forward) && 
        board.getPiece(next_pos_forward) == nullptr) {
        possible_moves.push_back(next_pos_forward);
    }

    // İlk hamlede iki kare ileri hareket
    // JSON'dan gelen `first_move_forward` kuralı kontrol edilir.
    if (!m_has_moved && m_movement_rules.first_move_forward >= 2) {
        Position double_step_pos;
        double_step_pos = {
            m_current_position.x, 
            m_current_position.y + 2 * direction
        };
        
        Position intermediate_pos; 
        intermediate_pos = {
            m_current_position.x, 
            m_current_position.y + direction
        }; // Aradaki kare
        
        
        if (board.checkBoundCorrect(double_step_pos) && 
        board.getPiece(double_step_pos) == nullptr && 
        board.getPiece(intermediate_pos) == nullptr) {
            possible_moves.push_back(double_step_pos);
        }
    }

    // Çapraz yakalama hareketleri
    // JSON'dan gelen `diagonal_capture` kuralı kontrol edilir.
    if (m_movement_rules.diagonal_capture >= 1) {
        Position capture_left;
        capture_left = {
            m_current_position.x - 1, 
            m_current_position.y + direction
        };
        
        Position capture_right;
        capture_right = {
            m_current_position.x + 1, 
            m_current_position.y + direction
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

    // TODO: En passant ve promotion mantığı burada veya MoveValidator'da daha detaylı ele alınabilir.

    return possible_moves;
}
*/


/*
// Piyon hamlesinin geçerliliğini kontrol eden implementasyon
bool Pawn::isValidMove(const Position& start, const Position& end, const ChessBoard& board) const {
    if (start.x == end.x && start.y == end.y) return false;
    if (!board.checkBoundCorrect(end)) return false;

    int dx = end.x - start.x;
    int dy = end.y - start.y;
    int direction = (m_color == "white") ? 1 : -1;

    Pieces* target_piece = board.getPiece(end);

    // Normal ileri hareket (1 kare)
    if (dx == 0 && dy == direction) {
        return target_piece == nullptr; // Hedef kare boş olmalı
    }
    // İlk hamle iki kare ileri
    if (!m_has_moved && dx == 0 && dy == 2 * direction && m_movement_rules.first_move_forward >= 2) {
        Position intermediate_pos;
        intermediate_pos = {
            start.x,
            start.y + direction
        };
        return target_piece == nullptr && board.getPiece(intermediate_pos) == nullptr;
    }
    // Çapraz yakalama
    if (m_movement_rules.diagonal_capture >= 1 && std::abs(dx) == 1 && dy == direction) {
        return target_piece != nullptr && target_piece -> getColor() != m_color; // Hedefte düşman taşı olmalı
    }

    // TODO: En passant kontrolü eklenecek.

    return false;
}
*/
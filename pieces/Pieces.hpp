#ifndef PIECES_HPP
#define PIECES_HPP

#include "../include/ConfigReader.hpp"
//#include "../chess_board/ChessBoard.hpp"
#include <iostream>
#include <string>

class ChessBoard;

class Pieces{
    public:
        Pieces(const std::string& type, const std::string& color,
                        const Movement& movement, const SpecialAbilities& special_abilities);
    
        ~Pieces() = default;
      
        std::string getType() const;
        std::string getColor() const;
        void setCurrentPosition(const Position& position);
        
        const Movement& getMovementRules() const;
        const SpecialAbilities& getSpecialAbilities() const;

        bool hasMoved() const;
        void setHasMoved(bool moved);

        std::string getUnicodeSymbol();
        /*
        virtual std::vector<Position> getPossibleMoves(const ChessBoard& board) const = 0;

        // Belirli bir hamlenin geçerli olup olmadığını kontrol eder.
        virtual bool isValidMove(const Position& start, const Position& end, const ChessBoard& board) const = 0;
            */
    protected:   
        std::string m_type; // Taşın türü (King, Queen, Pawn, Custom vb.)
        std::string m_color; // Taşın rengi (white, black)
        Position m_current_position; // Taşın mevcut pozisyonu
        Movement m_movement_rules; // Taşın hareket yetenekleri
        SpecialAbilities m_special_abilities; // Taşın özel yetenekleri
        bool m_has_moved;

};

class Pawn;
class Knight;
class Bishop;
class Rook;
class Queen;
class King;
class CustomPiece;

#endif //PIECES_HPP
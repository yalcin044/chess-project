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
        
        virtual std::vector<Position> getPossibleMoves(const ChessBoard& board) const = 0;
        virtual bool isValidMove(const Position& start, const Position& end, const ChessBoard& board) const = 0;
            
    protected:   
        std::string m_type; 
        std::string m_color; 
        Position m_current_position; 
        Movement m_movement_rules; 
        SpecialAbilities m_special_abilities; 
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
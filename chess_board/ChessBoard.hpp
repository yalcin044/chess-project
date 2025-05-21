#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

//#include "../pieces/Pieces.hpp"  // ya da projenizin dizin yapısına göre doğru yol
#include "../include/ConfigReader.hpp"
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

class Pieces;

struct PositionHash {
    size_t operator()(const Position& p) const {
        // Basit bir hash fonksiyonu: x ve y koordinatlarını birleştirme
        // Daha karmaşık ve çarpışmaları azaltan hash fonksiyonları da yazılabilir.
        return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
    }
};

// Position struct'ının eşitliğini kontrol etmek için operatör overload'ı
// Unordered_map'in doğru çalışması için gereklidir.
inline bool operator==(const Position& lhs, const Position& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

class ChessBoard{
    public:
        ChessBoard(const GameConfig& config);

        Pieces* getPiece(const Position& position) const;
        void placePiece(const Position& position, std::unique_ptr<Pieces> piece);
        //std::unique_ptr<Pieces> removePiece(const Position&  position);
        
        bool checkBoundCorrect(const Position& position) const;
        void getBoard() const;
    private:
        int m_board_size;
        std::unordered_map<Position, std::unique_ptr<Pieces>, PositionHash> board_chess;
       
        std::unique_ptr<Pieces> createPiece(const std::string& type, const std::string& color,
                                       const Movement& movement, const SpecialAbilities& special_abilities);
        
};


#endif //CHESSBOARD_HPP
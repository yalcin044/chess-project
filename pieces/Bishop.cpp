#include "Bishop.hpp"     // Kendi başlık dosyasını dahil et
#include "Pieces.hpp"   // ChessBoard'a erişim için (getPieceAt, isWithinBounds)
#include "../chess_board/ChessBoard.hpp"
#include <cmath>        // std::abs için

Bishop::Bishop(const std::string& color, const Movement& movement, const SpecialAbilities& special_abilities)
    : Pieces("Bishop", color, movement, special_abilities) {}
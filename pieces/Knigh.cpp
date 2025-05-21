#include "Knight.hpp"     // Kendi başlık dosyasını dahil et
#include "Pieces.hpp"   // ChessBoard'a erişim için (getPieceAt, isWithinBounds)
#include "../chess_board/ChessBoard.hpp"
#include <cmath>        // std::abs için

Knight::Knight(const std::string& color, const Movement& movement, const SpecialAbilities& special_abilities)
    : Pieces("Knight", color, movement, special_abilities) {}
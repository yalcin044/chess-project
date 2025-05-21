#include "Queen.hpp"     // Kendi başlık dosyasını dahil et
#include "Pieces.hpp"   // ChessBoard'a erişim için (getPieceAt, isWithinBounds)
#include "../chess_board/ChessBoard.hpp"
#include <cmath>        // std::abs için

Queen::Queen(const std::string& color, const Movement& movement, const SpecialAbilities& special_abilities)
    : Pieces("Queen", color, movement, special_abilities) {}
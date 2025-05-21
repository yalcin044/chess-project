
#include "ChessBoard.hpp" // Kendi başlık dosyasını dahil et
#include "../pieces/Pawn.hpp"       // Her bir taş türü için başlık dosyalarını dahil etmeliyiz
#include "../pieces/Knight.hpp"     // createPiece fonksiyonunda somut sınıfları oluştururken ihtiyaç duyulur
#include "../pieces/Bishop.hpp"
#include "../pieces/Rook.hpp"
#include "../pieces/Queen.hpp"
#include "../pieces/King.hpp"

/*
#include "CustomPiece.hpp"
*/

#include "../pieces/Pieces.hpp"


ChessBoard::ChessBoard(const GameConfig& config)
    : m_board_size(config.game_settings.board_size) {
    
    // Tahtayı kurucu içinde doğrudan doldur
    // Standart taşları yerleştir
    for (const auto& piece_config : config.pieces) {
        for (const auto& color_positions : piece_config.positions) {
            std::string color = color_positions.first; // "white" veya "black"
            for (const auto& position : color_positions.second) {
                std::unique_ptr<Pieces> piece = createPiece(piece_config.type, color,
                                                           piece_config.movement, piece_config.special_abilities);
                if (piece) {
                    piece -> setCurrentPosition(position); // Taşın kendi pozisyon bilgisini de ayarla
                    placePiece(position, std::move(piece)); // Tahtaya yerleştir
                }
            }
        }
    }

    // Özel taşları yerleştir (eğer varsa)
    for (const auto& piece_config : config.custom_pieces) {
        for (const auto& color_positions : piece_config.positions) {
            std::string color = color_positions.first;
            for (const auto& position : color_positions.second) {
                std::unique_ptr<Pieces> piece = createPiece(piece_config.type, color,
                                                           piece_config.movement, piece_config.special_abilities);
                if (piece) {
                    piece -> setCurrentPosition(position);
                    placePiece(position, std::move(piece));
                }
            }
        }
    }
}

Pieces* ChessBoard::getPiece(const Position& position) const {
    auto it = board_chess.find(position);
    
    if (it != board_chess.end()){
        return it -> second.get();
    }
    return nullptr;
}

void ChessBoard::placePiece(const Position& position, std::unique_ptr<Pieces> piece) { //exception yaz
    if (checkBoundCorrect(position))
        board_chess[position] = std::move(piece);
}
/*
std::unique_ptr<Pieces> ChessBoard::removePiece(const Position&  position) {
    
}
*/
bool ChessBoard::checkBoundCorrect(const Position& position) const {
    if (position.x >= 0 &&  position.x <= m_board_size && 
        position.y >= 0 && position.y <= m_board_size){
        return true;
    }
    else{
        return false;
    }
}

void ChessBoard::getBoard() const{
    for (int y = m_board_size; y != 0; y--){
        std::cout << y << " ";
        
        for (int x = 0; x < m_board_size; x++){
            Position position{x, y - 1};
            auto it = board_chess.find(position);
            
            if (it != board_chess.end() && it -> second){
                std::cout << it -> second -> getUnicodeSymbol() << " ";
            }
            else {
                std::cout << ". ";
            }
        }
        std::cout << "\n";
    }

    std::cout << "  ";
    for (char c = 'a'; c < 'a' + m_board_size; c++){
        std::cout << c << " ";
    }
    std::cout << std::endl;
}

//Yardımcı metod: Belirli bir PieceConfig'den Piece nesnesi oluşturur.
// Bu, Polymorphism'i kullanarak doğru türetilmiş sınıfı oluşturduğumuz "Fabrika" metodumuz.
std::unique_ptr<Pieces> ChessBoard::createPiece(const std::string& type, const std::string& color,
                                               const Movement& movement, const SpecialAbilities& special_abilities) {
    if (type == "Pawn") {
        return std::make_unique<Pawn>(color, movement, special_abilities);
    } else if (type == "Knight") {
        return std::make_unique<Knight>(color, movement, special_abilities);
    } else if (type == "Bishop") {
        return std::make_unique<Bishop>(color, movement, special_abilities);
    } else if (type == "Rook") {
        return std::make_unique<Rook>(color, movement, special_abilities);
    } else if (type == "Queen") {
        return std::make_unique<Queen>(color, movement, special_abilities);
    }
    else if (type == "King") {
        return std::make_unique<King>(color, movement, special_abilities);
    }
    
    /*
    // Eğer tanımsız veya özel bir taş türü ise CustomPiece olarak oluştur
    return std::make_unique<CustomPiece>(type, color, movement, special_abilities);
    */
   return nullptr;
}

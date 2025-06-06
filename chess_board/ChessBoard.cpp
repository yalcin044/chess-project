
#include "ChessBoard.hpp" 
#include "../pieces/Pawn.hpp"       
#include "../pieces/Knight.hpp"     
#include "../pieces/Bishop.hpp"
#include "../pieces/Rook.hpp"
#include "../pieces/Queen.hpp"
#include "../pieces/King.hpp"
#include "../pieces/Pieces.hpp"


ChessBoard::ChessBoard(const GameConfig& config)
    : m_board_size(config.game_settings.board_size) {
    
  
    for (const auto& piece_config : config.pieces) {
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

void ChessBoard::placePiece(const Position& position, std::unique_ptr<Pieces> piece) {
    if (checkBoundCorrect(position))
        board_chess[position] = std::move(piece);
}

std::unique_ptr<Pieces> ChessBoard::removePiece(const Position& position) {
    auto it = board_chess.find(position);
    if (it != board_chess.end()) {
        std::unique_ptr<Pieces> removed_piece = std::move(it->second); 
        board_chess.erase(it); 
        return removed_piece; 
    }
    return nullptr; 
}

bool ChessBoard::movePiece(const Position& start, const Position& end) {
    
    Pieces* moving_piece_raw = getPiece(start);
    if (moving_piece_raw == nullptr) {
       
       
        std::cerr << "There is no such piece: (" << start.x << "," << start.y << ")" << std::endl;
        return false;
    }

    if (!moving_piece_raw->isValidMove(start, end, *this)) {
        std::cerr << "Invalid move: (" << start.x << "," << start.y << ") -> (" << end.x << "," << end.y << ")" << std::endl;
        return false;
    }

    std::unique_ptr<Pieces> captured_piece = nullptr;
    if (getPiece(end) != nullptr) {
        captured_piece = removePiece(end); 
    }

    std::unique_ptr<Pieces> piece_to_move = removePiece(start);
    if (piece_to_move == nullptr) {
        
        return false;
    }

    piece_to_move->setCurrentPosition(end);

    piece_to_move->setHasMoved(true);


    placePiece(end, std::move(piece_to_move)); 


    return true;
}

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
    } else if (type == "King") {
        return std::make_unique<King>(color, movement, special_abilities);
    }
    
   return nullptr;
}

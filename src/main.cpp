#include "../include/ConfigReader.hpp"
#include "../chess_board/ChessBoard.hpp"
#include "../pieces/Pieces.hpp"
#include "../portal/PortalSystem.hpp"
#include <iostream>
#include <string>

// Helper function to display special abilities
void displaySpecialAbilities(const SpecialAbilities &abilities) {
  if (abilities.castling)
    std::cout << "Castling ";
  if (abilities.royal)
    std::cout << "Royal ";
  if (abilities.jump_over)
    std::cout << "Jump-over ";
  if (abilities.promotion)
    std::cout << "Promotion ";
  if (abilities.en_passant)
    std::cout << "En-passant ";

  // Display any custom abilities
  for (const auto &[key, value] : abilities.custom_abilities) {
    if (value) {
      std::cout << key << " ";
    }
  }
}

// Helper function to display piece information
void displayPieceInfo(const PieceConfig &piece) {
  std::cout << "Type: " << piece.type << " (Count: " << piece.count << ")"
            << std::endl;

  // Show movement info
  std::cout << "  Movement: ";
  if (piece.movement.forward > 0)
    std::cout << "Forward: " << piece.movement.forward << " ";
  if (piece.movement.sideways > 0)
    std::cout << "Sideways: " << piece.movement.sideways << " ";
  if (piece.movement.diagonal > 0)
    std::cout << "Diagonal: " << piece.movement.diagonal << " ";
  if (piece.movement.l_shape)
    std::cout << "L-shape: Yes ";
  if (piece.movement.diagonal_capture > 0)
    std::cout << "Diagonal Capture: " << piece.movement.diagonal_capture << " ";
  if (piece.movement.first_move_forward > 0)
    std::cout << "First Move Forward: " << piece.movement.first_move_forward
              << " ";
  std::cout << std::endl;

  // Show special abilities
  std::cout << "  Special Abilities: ";
  displaySpecialAbilities(piece.special_abilities);
  std::cout << std::endl;

  // Display positions
  if (piece.positions.count("white") > 0) {
    std::cout << "  White positions: ";
    for (const auto &pos : piece.positions.at("white")) {
      std::cout << "(" << pos.x << "," << pos.y << ") ";
    }
    std::cout << std::endl;
  }

  if (piece.positions.count("black") > 0) {
    std::cout << "  Black positions: ";
    for (const auto &pos : piece.positions.at("black")) {
      std::cout << "(" << pos.x << "," << pos.y << ") ";
    }
    std::cout << std::endl;
  }
}

int main(int argc, char *argv[]) {
  std::string configPath = "data/chess_pieces.json";

  // If a command-line argument is provided, use it as the config path
  if (argc > 1) {
    configPath = argv[1];
  }

  ConfigReader configReader;

  // Load the configuration
  if (!configReader.loadFromFile(configPath)) {
    std::cerr << "Failed to load configuration. Exiting." << std::endl;
    return 1;
  }

  // Get the parsed configuration
  const GameConfig &config = configReader.getConfig();

  // Display some information from the config
  std::cout << "==== Game Configuration ====" << std::endl;
  std::cout << "Game: " << config.game_settings.name << std::endl;
  std::cout << "Board size: " << config.game_settings.board_size << "x"
            << config.game_settings.board_size << std::endl;
  std::cout << "Turn limit: " << config.game_settings.turn_limit << std::endl;

  // Display standard pieces information
  std::cout << "\n==== Standard Pieces ====" << std::endl;
  for (const auto &piece : config.pieces) {
    displayPieceInfo(piece);
  }

  // Display custom pieces information if any
  if (!config.custom_pieces.empty()) {
    std::cout << "\n==== Custom Pieces ====" << std::endl;
    for (const auto &piece : config.custom_pieces) {
      displayPieceInfo(piece);
    }
  }

  // Display portals information
  std::cout << "\n==== Portals ====" << std::endl;
  for (const auto &portal : config.portals) {
    std::cout << "Portal ID: " << portal.id << std::endl;
    std::cout << "  Entry: (" << portal.positions.entry.x << ","
              << portal.positions.entry.y << ")" << std::endl;
    std::cout << "  Exit: (" << portal.positions.exit.x << ","
              << portal.positions.exit.y << ")" << std::endl;
    std::cout << "  Preserve direction: "
              << (portal.properties.preserve_direction ? "Yes" : "No")
              << std::endl;
    std::cout << "  Cooldown: " << portal.properties.cooldown << " turns"
              << std::endl;

    std::cout << "  Allowed colors: ";
    for (const auto &color : portal.properties.allowed_colors) {
      std::cout << color << " ";
    }
    std::cout << std::endl;
  }

  std::cout << "\n";
  ChessBoard chess(config);
  chess.getBoard();
  PortalSystem portalSystem(config.portals, chess);
  std::string line;
  std::string command;
  std::string from_str, to_str;

  while (true) {
      std::cout << "\nEnter command (E.g. move e2 e4, undo, quit): ";

      std::getline(std::cin, line);
      std::stringstream ss(line);
      ss >> command; 

      if (command == "quit" || command == "exit") {
          std::cout << "Game exited." << std::endl;
          break;
      } else if (command == "undo") {
          std::cout << "Undo done." << std::endl;
          
      } else if (command == "move") {
          ss >> from_str >> to_str;

          Position start_pos;
          if (from_str.length() == 2) {
              start_pos.x = from_str[0] - 'a';
              start_pos.y = (from_str[1] - '0') - 1;
          } else {
              std::cerr << "WARNING: Invalid 'from' format. Using default invalid position." << std::endl;
              start_pos = {-1, -1};
          }

          Position end_pos;
          if (to_str.length() == 2) {
              end_pos.x = to_str[0] - 'a';
              end_pos.y = (to_str[1] - '0') - 1;
          } else {
              std::cerr << "WARNING: Invalid 'to' format. Using default invalid position." << std::endl;
              end_pos = {-1, -1};
          }
          
          if (start_pos.x == -1 || start_pos.y == -1 || end_pos.x == -1 || end_pos.y == -1) {
              std::cout << "Invalid positions detected. Please check." << std::endl;
              continue;
          }
      
          bool move_successful = chess.movePiece(start_pos, end_pos);

          if (move_successful) {
              std::cout << "Move made successfully." << std::endl;
              chess.getBoard(); 
         
              Pieces* moved_piece_check = chess.getPiece(end_pos); 
              if (moved_piece_check != nullptr) { 
                   std::string moved_piece_color = moved_piece_check->getColor(); 
                  
                  if (portalSystem.isPortalUsable(end_pos, moved_piece_color)) {
                      std::cout << "A piece landed on a portal entry. Attempting automatic teleportation..." << std::endl;
             
                      if (portalSystem.teleportPiece(end_pos, moved_piece_color)) {
                          std::cout << "Piece successfully teleported." << std::endl;
                          chess.getBoard(); 
                      } else {
                          std::cout << "Portal teleportation failed." << std::endl;
                      }
                  }
              }

          } else {
              std::cout << "Move failed. Please make a valid move." << std::endl;
          }

      } else {
          std::cout << "Unknown command: '" << command << "'. Plaese use move, undo, quit or exit." << std::endl;
      }
  }

  return 0;
}

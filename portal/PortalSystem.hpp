// portal_system/PortalSystem.hpp
#ifndef PORTALSYSTEM_HPP
#define PORTALSYSTEM_HPP

#include "../include/ConfigReader.hpp"
#include "../data_structures/Queue.hpp"
#include "../chess_board/ChessBoard.hpp"
#include <vector>
#include <unordered_map>
#include <string>

struct PortalState {
    std::string id;
    Position entry_pos;
    Position exit_pos;
    int remaining_cooldown;
    int original_cooldown_duration; 
    bool preserve_direction;
    std::vector<std::string> allowed_colors;
};

class PortalSystem {
    public:
        PortalSystem(const std::vector<PortalConfig>& portalConfigs, ChessBoard& board);

        bool teleportPiece(const Position& current_pos, std::string& piece_color);
        void updateCooldowns();
        bool isPortalUsable(const Position& portal_entry_pos, const std::string& piece_color) const;

    private:
        std::unordered_map<std::string, PortalState> m_portals;
        Queue m_cooldownQueue;
        ChessBoard& m_board; 
};

#endif // PORTALSYSTEM_HPP
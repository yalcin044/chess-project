#include "PortalSystem.hpp"
#include <iostream>
#include "../pieces/Pieces.hpp" 

PortalSystem::PortalSystem(const std::vector<PortalConfig>& portalConfigs, ChessBoard& board)
    : m_board(board) {
    for (const auto& config : portalConfigs) {
        PortalState state;
        state.id = config.id;
        state.entry_pos = config.positions.entry;
        state.exit_pos = config.positions.exit;
        state.remaining_cooldown = 0;
        state.original_cooldown_duration = config.properties.cooldown; 
        state.preserve_direction = config.properties.preserve_direction;
        state.allowed_colors = config.properties.allowed_colors;
        m_portals[config.id] = state;
    }
}

bool PortalSystem::isPortalUsable(const Position& portal_entry_pos, const std::string& piece_color) const {
    for (const auto& pair : m_portals) {
        const PortalState& portal = pair.second;
        if (portal.entry_pos == portal_entry_pos) {
            if (portal.remaining_cooldown > 0) {
                std::cout << "Portal " << portal.id << " is on cooldown (" << portal.remaining_cooldown << " turns left)." << std::endl;
                return false;
            }
            bool color_allowed = false;
            if (portal.allowed_colors.empty()) {
                color_allowed = true;
            } else {
                for (const auto& allowed_c : portal.allowed_colors) {
                    if (allowed_c == piece_color) {
                        color_allowed = true;
                        break;
                    }
                }
            }
            if (!color_allowed) {
                std::cout << "Portal " << portal.id << " cannot be used by this color piece." << std::endl;
                return false;
            }
            return true;
        }
    }
    return false;
}

bool PortalSystem::teleportPiece(const Position& current_pos, std::string& piece_color) {
    std::string portal_id_to_use;
    Position exit_pos;
    bool found_portal = false;

    for (const auto& pair : m_portals) {
        const PortalState& portal = pair.second;
        if (portal.entry_pos == current_pos) {
            portal_id_to_use = portal.id;
            exit_pos = portal.exit_pos;
            found_portal = true;
            break;
        }
    }

    if (!found_portal) {
        std::cout << "No portal entry found at the specified position." << std::endl;
        return false;
    }

    if (!isPortalUsable(current_pos, piece_color)) {
        return false;
    }

    std::unique_ptr<Pieces> piece_to_teleport = m_board.removePiece(current_pos);
    if (!piece_to_teleport) {
        std::cerr << "Error: No piece found at portal entry." << std::endl;
        return false;
    }

    if (m_board.getPiece(exit_pos) != nullptr) {
        std::cout << "Portal exit square is occupied. Cannot teleport." << std::endl;
        m_board.placePiece(current_pos, std::move(piece_to_teleport)); 
        return false;
    }

    piece_to_teleport->setCurrentPosition(exit_pos);
    m_board.placePiece(exit_pos, std::move(piece_to_teleport)); 

    m_portals[portal_id_to_use].remaining_cooldown = m_portals[portal_id_to_use].original_cooldown_duration;
    m_cooldownQueue.enqueue(portal_id_to_use);

    std::cout << "Piece successfully teleported! Portal " << portal_id_to_use << " entered cooldown." << std::endl;
    return true;
}

void PortalSystem::updateCooldowns() {
    int queue_size_at_start_of_turn = m_cooldownQueue.getSize();
    for (int i = 0; i < queue_size_at_start_of_turn; ++i) {
        std::string portal_id = m_cooldownQueue.getFront();
        m_cooldownQueue.dequeue();

        if (m_portals.count(portal_id)) {
            m_portals[portal_id].remaining_cooldown--;
            if (m_portals[portal_id].remaining_cooldown > 0) {
                m_cooldownQueue.enqueue(portal_id);
            } else {
                std::cout << "Portal " << portal_id << " cooldown ended." << std::endl;
            }
        }
    }
}
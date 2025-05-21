#include "Pieces.hpp"

Pieces::Pieces(const std::string& type, const std::string& color,
                        const Movement& movement, const SpecialAbilities& special_abilities) 
                        : m_type(type), m_color(color), m_movement_rules(movement), m_special_abilities(special_abilities), m_has_moved(false) { }

std::string Pieces::getType() const {
    return m_type;
}

std::string Pieces::getColor() const {
    return m_color;
}

void Pieces::setCurrentPosition(const Position& position) {
    m_current_position = position;
}
/*
const Movement& Pieces::getMovementRules() const {
    return m_movement_rules;
}

const SpecialAbilities& Pieces::getSpecialAbilities() const {
    return m_special_abilities;
}
*/
bool Pieces::hasMoved() const {
    return m_has_moved;
}

void Pieces::setHasMoved(bool moved) {
    m_has_moved = moved;
} 

std::string Pieces::getUnicodeSymbol(){
    std::string color = getColor();
    std::string type = getType();
    
    if (color == "white"){
        if (type == "King") return "♔";
        if (type == "Queen") return "♕";
        if (type == "Rook") return "♖";
        if (type == "Bishop") return "♗";
        if (type == "Knight") return "♘";
        if (type == "Pawn") return "♙";
    }
    else if (color == "black"){
        if (type == "King") return "♚";
        if (type == "Queen") return "♛";
        if (type == "Rook") return "♜";
        if (type == "Bishop") return "♝";
        if (type == "Knight") return "♞";
        if (type == "Pawn") return "♟";
    } 

    return " ";
}
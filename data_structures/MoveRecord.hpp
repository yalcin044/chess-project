// include/MoveRecord.hpp
#ifndef MOVERECORD_HPP
#define MOVERECORD_HPP

#include "../include/ConfigReader.hpp" 
#include <string> 


struct MoveRecord {
    Position start_pos; 
    Position end_pos; 
    std::string moving_piece_type; 
    std::string moving_piece_color; 
    
    bool captured_piece_exists; 
    std::string captured_piece_type; 
    std::string captured_piece_color; 

    bool had_moved_before; 

    // Default constructor
    MoveRecord() :
        captured_piece_exists(false),
        had_moved_before(false) {}
};

#endif // MOVERECORD_HPP
//
// Created by jvanz on 5/1/2024.
//

#ifndef INC_455_FINAL_JULIA_SETS_JULIASET_HPP
#define INC_455_FINAL_JULIA_SETS_JULIASET_HPP


#include "SFML/System/Vector2.hpp"

class JuliaSet {
public:
    JuliaSet(sf::Vector2f const_c_, int max_iterations_) : const_c(const_c_), MAX_ITERATIONS(max_iterations_){
    }

    const sf::Vector2f const_c;
    const int MAX_ITERATIONS;
    float iterate_coordinate(sf::Vector2f zi);

    float smooth_iterate(sf::Vector2f zi);
};


#endif //INC_455_FINAL_JULIA_SETS_JULIASET_HPP

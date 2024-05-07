//
// Created by jvanz on 5/6/2024.
//

#ifndef INC_455_FINAL_JULIA_SETS_GRADIENTS_HPP
#define INC_455_FINAL_JULIA_SETS_GRADIENTS_HPP


#include "SFML/Graphics/Color.hpp"

enum class Gradient {
    BLACK_TO_BLUE,
    BLACK_AND_WHITE
};

class Gradients {
public:
    static sf::Color applyGradient(float iter_ratio, Gradient gradient) {
        sf::Color returnColor = sf::Color::Black;

        switch (gradient) {
            case Gradient::BLACK_AND_WHITE:
                returnColor = sf::Color((iter_ratio * 255.0f), (iter_ratio * 255.0f), (iter_ratio * 255.0f));
                break;
            case Gradient::BLACK_TO_BLUE:
                if (iter_ratio <= -1.0f) {
                    returnColor = sf::Color::Black;
                    break;
                } else if (iter_ratio < 1.0f) {
                    double redResult = 0.0f + iter_ratio * (34.0f - 0.0f);
                    double greenResult = 0.0f + iter_ratio * (221.0f - 0.0f);
                    double blueResult = 0.0f + iter_ratio * (241.0f - 0.0f);
                    returnColor = sf::Color(redResult, greenResult, blueResult);
                    break;
                } else {
                    returnColor = sf::Color::Black;
                    break;
                }
            default:
                returnColor = sf::Color::Black;
                break;
        }
        return returnColor;
    }

};

#endif //INC_455_FINAL_JULIA_SETS_GRADIENTS_HPP

//
// Created by jvanz on 5/6/2024.
//

#ifndef INC_455_FINAL_JULIA_SETS_GRADIENTS_HPP
#define INC_455_FINAL_JULIA_SETS_GRADIENTS_HPP


#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector3.hpp"

enum class Gradient {
    BLACK_TO_BLUE,
    BLACK_AND_WHITE,
    DARK_MULTICOLOR
};

/*
 * Good color points to use on a gradient for Julia fractals
 * 0.0f (lower bound, usually black)
 * 0.03f
 * 0.05f
 * 0.25f
 * 0.5f
 * 0.85f
 * 0.95f
 * 1.0f (max iters)
 */

class Gradients {
public:
    static sf::Vector3f applyGradient(float iter_ratio, Gradient gradient) {
        sf::Vector3f returnColor = sf::Vector3f{0.0f, 0.0f, 0.0f};

        std::vector<std::tuple<float, sf::Vector3f>> colorPoints = gradientMappings(gradient);
        if (iter_ratio >= 1.0f) {
            return std::get<1>(colorPoints.back());
        } else if (iter_ratio <= 0.0f) {
            return std::get<1>(colorPoints.front());
        }
        int i = 0;
        for (std::tuple<float, sf::Vector3f> point: colorPoints) {
            if (iter_ratio < std::get<0>(point)) {
                sf::Vector3f currIndex = std::get<1>(point);
                float range = std::get<0>(point) - std::get<0>(colorPoints[i - 1]);
                float pos = iter_ratio - std::get<0>(colorPoints[i - 1]);
                float ratio = pos / range;

                float red = (1.0f - ratio) * std::get<1>(colorPoints[i - 1]).x + ratio * currIndex.x;
                float green = (1.0f - ratio) * std::get<1>(colorPoints[i - 1]).y + ratio * currIndex.y;
                float blue = (1.0f - ratio) * std::get<1>(colorPoints[i - 1]).z + ratio * currIndex.z;
                returnColor = sf::Vector3f(red, green, blue);
                break;
            }
            ++i;
        }
        return returnColor;
    }

    static std::vector<std::tuple<float, sf::Vector3f>> gradientMappings(Gradient gradient) {
        std::vector<std::tuple<float, sf::Vector3f>> colorPoints;
        switch (gradient) {
            case Gradient::BLACK_AND_WHITE:
                colorPoints.emplace_back(0.0f, sf::Vector3f{0.0f, 0.0f, 0.0f});
                colorPoints.emplace_back(1.0f, sf::Vector3f{255.0f, 255.0f, 255.0f});
                break;
            case Gradient::BLACK_TO_BLUE:
                colorPoints.emplace_back(-1.0f, sf::Vector3f{0.0f, 0.0f, 0.0f});
                colorPoints.emplace_back(0.25f, sf::Vector3f(34.0f, 221.0f, 241.0f));
                colorPoints.emplace_back(1.0f, sf::Vector3f{0.0f, 0.0f, 0.0f});
                break;
            case Gradient::DARK_MULTICOLOR:
                colorPoints.emplace_back(0.0f, sf::Vector3f(25, 24, 23));
                colorPoints.emplace_back(0.03f, sf::Vector3f(120, 90, 70));
                colorPoints.emplace_back(0.05f, sf::Vector3f(130, 24, 23));
                colorPoints.emplace_back(0.25f, sf::Vector3f(250, 179, 100));
                colorPoints.emplace_back(0.5f, sf::Vector3f(43, 65, 98));
                colorPoints.emplace_back(0.85f, sf::Vector3f(11, 110, 79));
                colorPoints.emplace_back(0.95f, sf::Vector3f(150, 110, 79));
                colorPoints.emplace_back(1.0f, sf::Vector3f(255, 255, 255));
                break;
            default:
                colorPoints.emplace_back(1.0f, sf::Vector3f{0.0f, 0.0f, 0.0f});
                break;
        }
        return colorPoints;
    }

    static sf::Color vec3ToColor(sf::Vector3f v) {
        return {
                static_cast<uint8_t>(std::min(std::max(0.0f, v.x), 255.0f)),
                static_cast<uint8_t>(std::min(std::max(0.0f, v.y), 255.0f)),
                static_cast<uint8_t>(std::min(std::max(0.0f, v.z), 255.0f)),
        };
    }

};

#endif //INC_455_FINAL_JULIA_SETS_GRADIENTS_HPP

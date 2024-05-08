//
// Created by jvanz on 5/1/2024.
//

#ifndef INC_455_FINAL_JULIA_SETS_RENDER_HPP
#define INC_455_FINAL_JULIA_SETS_RENDER_HPP


#include <random>
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "utils/JuliaSet.hpp"

class Render {

public:
    Render() {
        mt = std::mt19937(1);
        curr_julia = {-0.71f, 0.25f};
    }

    std::thread startRenderThread(sf::RenderWindow &window);

    void captureWindow();

private:

    sf::Vector2f curr_julia;

    void renderWindow(sf::RenderWindow *window);

    bool capture = false;

    sf::Image generateVertexArray(sf::Vector2u window_size);
    std::mt19937 mt;
    float RNG(float max) {
        std::uniform_real_distribution<float> dist(0.0f, max);
        return dist(mt);
    }

    void
    computeSlice(sf::Vector2u window_size, int k, int slice_height, std::array<sf::Vector2f, 32> anti_aliasing_offsets,
                 int MAX_ITERATIONS, JuliaSet &js, sf::Image &img);
};


#endif //INC_455_FINAL_JULIA_SETS_RENDER_HPP

//
// Created by jvanz on 5/1/2024.
//

#include <thread>
#include <string>
#include <iostream>
#include "Render.hpp"
#include "utils/JuliaSet.hpp"
#include "SFML/Graphics/VertexArray.hpp"

void Render::renderWindow(sf::RenderWindow *window) {
    window->setActive(true);
    sf::VertexArray image = generateVertexArray(window->getSize());
    std::cout << "finished" << std::endl;

    while (window->isOpen()) {
        //draw
        window->clear();
        window->draw(image);
        // render
        window->display();
    }
}

sf::VertexArray Render::generateVertexArray(sf::Vector2u window_size) {
    const int MAX_ITERATIONS = 250;
    auto js = JuliaSet({-0.75f, 0.21f}, MAX_ITERATIONS);
    sf::VertexArray va(sf::Points, (window_size.x * window_size.y));
    int idx = 0;
    for (int x{0}; x < window_size.x; ++x) {
        for (int y{0}; y < window_size.y; ++y) {
            // Ensure window size x and y are even numbers please for the love of god
            float scale = window_size.y / 2.0f;
            sf::Vector2f curr_coordinate = {(x - (window_size.x / 2.0f)), (y - (window_size.y / 2.0f))};
            const float julia_iters = js.smooth_iterate((curr_coordinate / scale));
            const float iter_ratio = (julia_iters / static_cast<float>(MAX_ITERATIONS)) * 255.0f;
            sf::Vertex vertex;
            vertex.position = {static_cast<float>(x),static_cast<float>(y)};
            vertex.color = sf::Color(iter_ratio, iter_ratio, iter_ratio);
            va[idx++] = vertex;
        }
    }
    return va;
}



std::thread Render::startRenderThread(sf::RenderWindow &window) {
    std::thread thread(&Render::renderWindow, this, &window);
    return thread;
}






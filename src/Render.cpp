//
// Created by jvanz on 5/1/2024.
//

#include <thread>
#include <string>
#include <iostream>
#include <array>
#include <sstream>
#include <iomanip>
#include <charconv>
#include "Render.hpp"
#include "utils/JuliaSet.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "utils/Gradients.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

void Render::renderWindow(sf::RenderWindow *window) {
    window->setActive(true);
    sf::VertexArray image = generateVertexArray(window->getSize());
    std::cout << "finished" << std::endl;
    sf::Font font;
    if (!font.loadFromFile("../../src/resources/Insanibc.ttf")) {
        std::cout << "No Font!" << std::endl;
    }
    sf::Text label;
    label.setFont(font);
    std::string x = std::to_string(curr_julia.x).substr(0, std::to_string(curr_julia.x).find('.') + 3);
    std::string y = std::to_string(curr_julia.y).substr(0, std::to_string(curr_julia.y).find('.') + 3);

    std::string text = "  [" + x + ", " + y + "]  ";
    label.setString(text);
    label.setCharacterSize(24);
    label.setFillColor(sf::Color::White);
    label.setPosition(0.5, 0.5);

    while (window->isOpen()) {

        if (this->capture) {
            this->capture = false;
            std::cout << "Saving..." << std::endl;
            sf::Texture texture;
            texture.create(window->getSize().x, window->getSize().y);
            texture.update(*window);
            sf::Image img = texture.copyToImage();
            bool b = img.saveToFile("../../src/resources/capture.png");
            std::string eval = b ? "Saved." : "Failed.";
            std::cout << eval << std::endl;
        }
        //draw
        window->clear();
        window->draw(image);
        window->draw(label);
        // render
        window->display();

    }
}

sf::VertexArray Render::generateVertexArray(sf::Vector2u window_size) {
    const int MAX_ITERATIONS = 500;
    std::array<sf::Vector2f, 32> anti_aliasing_offsets;
    for (auto& o : anti_aliasing_offsets) {
        o.x = RNG(1.0f);
        o.y = RNG(1.0f);
        std::cout << o.x << "," << o.y << std::endl;
    }

    anti_aliasing_offsets[0] = {};

    auto js = JuliaSet(curr_julia, MAX_ITERATIONS);


    sf::VertexArray va(sf::Points, (window_size.x * window_size.y));
    int idx = 0;
    for (int x{0}; x < window_size.x; ++x) {
        for (int y{0}; y < window_size.y; ++y) {

            const int samples = 1;
            sf::Vertex vertex;
            sf::Vector3f colorSamples;
            for (int i{samples}; i--;) {
                // Ensure window size x and y are even numbers please for the love of god
                float scale = static_cast<float>(window_size.y) / 2.0f;
                sf::Vector2f rand = anti_aliasing_offsets[i];
                sf::Vector2f curr_coordinate = {(static_cast<float>(x) - (static_cast<float>(window_size.x) / 2.0f)) + rand.x, (static_cast<float>(y) - (static_cast<float>(window_size.y) / 2.0f)) + rand.y};
                const float julia_iters = js.iterate_coordinate((curr_coordinate / scale));
                const float iter_ratio = (julia_iters / static_cast<float>(MAX_ITERATIONS));
                vertex.position = {static_cast<float>(x), static_cast<float>(y)};
                sf::Vector3f c = Gradients::applyGradient(iter_ratio, Gradient::DARK_MULTICOLOR);
                colorSamples += c;
            }
            sf::Vector3f finalColor = colorSamples / float(samples);
            vertex.color = Gradients::vec3ToColor(finalColor);
            va[idx++] = vertex;
        }
    }
    return va;
}

void Render::captureWindow() {
    this->capture = true;
}


std::thread Render::startRenderThread(sf::RenderWindow &window) {
    std::thread thread(&Render::renderWindow, this, &window);
    return thread;
}






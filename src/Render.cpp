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
#include "SFML/Graphics/Sprite.hpp"

void Render::renderWindow(sf::RenderWindow *window) {
    window->setActive(true);
    sf::Image image = generateVertexArray(window->getSize());
    sf::Texture fractal;
    fractal.create(image.getSize().x, image.getSize().y);
    fractal.update(image);
    sf::Sprite fractal_sprite(fractal);
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
            bool b = img.saveToFile("../../src/resources/capture" + x + "_" + y + ".png");
            std::string eval = b ? "Saved." : "Failed.";
            std::cout << eval << std::endl;
        }
        //draw
        window->clear();
        window->draw(fractal_sprite);
        window->draw(label);
        // render
        window->display();

    }
}

sf::Image Render::generateVertexArray(sf::Vector2u window_size) {
    std::array<sf::Vector2f, 32> anti_aliasing_offsets;
    for (auto &o: anti_aliasing_offsets) {
        o.x = RNG(1.0f);
        o.y = RNG(1.0f);
        std::cout << o.x << "," << o.y << std::endl;
    }

    anti_aliasing_offsets[0] = {};

    JuliaSet js = JuliaSet(curr_julia, MAX_ITERATIONS);


    sf::Image image;
    image.create(window_size.x, window_size.y);

    int thread_count = 24;
    int slice_height = window_size.y / thread_count;
    std::vector<std::thread> thread_pool;
    for (int k{0}; k < thread_count; k++) {
        thread_pool.emplace_back(&Render::computeSlice, this, window_size, k, slice_height, anti_aliasing_offsets,
                                 MAX_ITERATIONS, std::ref(js), std::ref(image));
    }
    for (std::thread &t: thread_pool) {
        t.join();
    }
    return image;
}

void Render::captureWindow() {
    this->capture = true;
}

void Render::computeSlice(sf::Vector2u window_size, int k, int slice_height,
                          std::array<sf::Vector2f, 32> anti_aliasing_offsets, int MAX_ITERATIONS, JuliaSet &js,
                          sf::Image &img) {
    for (int x{0}; x < window_size.x; ++x) {
        for (int y{k * slice_height}; y < (k + 1) * slice_height; ++y) {
            const int samples = 16;
            sf::Vertex vertex;
            sf::Vector3f colorSamples;
            for (int i{samples}; i--;) {
                // Ensure window size x and y are even numbers please for the love of god
                float scale = static_cast<float>(window_size.y) / 2.0f;
                sf::Vector2f rand = anti_aliasing_offsets[i];
                sf::Vector2f curr_coordinate = {
                        (static_cast<float>(x) - (static_cast<float>(window_size.x) / 2.0f)) + rand.x,
                        (static_cast<float>(y) - (static_cast<float>(window_size.y) / 2.0f)) + rand.y};
                const float julia_iters = js.smooth_iterate((curr_coordinate / scale));
                const float iter_ratio = (julia_iters / static_cast<float>(MAX_ITERATIONS));
                vertex.position = {static_cast<float>(x), static_cast<float>(y)};
                sf::Vector3f c = Gradients::applyGradient(iter_ratio, Gradient::DARK_MULTICOLOR);
                colorSamples += c;
            }
            sf::Vector3f finalColor = colorSamples / float(samples);
            sf::Color color = Gradients::vec3ToColor(finalColor);
            img.setPixel(x, y, color);

        }
    }
}


std::thread Render::startRenderThread(sf::RenderWindow &window) {
    std::thread thread(&Render::renderWindow, this, &window);
    return thread;
}





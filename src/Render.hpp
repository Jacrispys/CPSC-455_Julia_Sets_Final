//
// Created by jvanz on 5/1/2024.
//

#ifndef INC_455_FINAL_JULIA_SETS_RENDER_HPP
#define INC_455_FINAL_JULIA_SETS_RENDER_HPP


#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/VertexArray.hpp"

class Render {

public:
    Render() = default;

    std::thread startRenderThread(sf::RenderWindow& window);

private:
    void renderWindow(sf::RenderWindow *window);

    sf::VertexArray generateVertexArray(sf::Vector2u window_size);
};


#endif //INC_455_FINAL_JULIA_SETS_RENDER_HPP

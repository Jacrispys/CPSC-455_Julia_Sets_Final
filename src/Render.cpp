//
// Created by jvanz on 5/1/2024.
//

#include <thread>
#include "Render.hpp"

void Render::renderWindow(sf::RenderWindow* window) {
    window->setActive(true);

    while (window->isOpen()) {
        //draw

        // render
        window->clear();
        window->display();
    }
}

std::thread Render::startRenderThread(sf::RenderWindow& window) {
    std::thread thread(&Render::renderWindow, this, &window);
    return thread;
}




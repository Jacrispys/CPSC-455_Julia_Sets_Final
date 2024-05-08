#include <SFML/Graphics.hpp>
#include <thread>
#include "Render.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920u, 1080u), "OpenGL");
    window.setFramerateLimit(144);
    window.setActive(false);

    Render render = Render();
    std::thread renderThread = render.startRenderThread(window);

    // event logic
    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::C) {
                    render.captureWindow();
                }
                }
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

        }
        renderThread.join();
        return 0;
    }

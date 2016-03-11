#include "Game.h"
#include <SFML/Graphics.hpp>

namespace Ilargia {

    inline float Game::deltaTime() {
        static sf::Clock clock;
        sf::Time elapsed = clock.restart();
        return elapsed.asMilliseconds();
    }

}
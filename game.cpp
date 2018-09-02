#include <iostream>

#include "game.h"

Game *Game::getInstance() {
    if (instance == 0) {
        instance = new Game();
    }
    return instance;
}

Game::Game() {
    std::cout << "yay" << std::endl;
}

Game *Game::instance = 0;
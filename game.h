#ifndef GAME_H
#define GAME_H

#define NUM_CARDS       16
#define NUM_GAME_CARDS  5
#define BOARD_SIZE      5

#include <array>
#include <iostream>
#include <stack>
#include "card.h"

class Card;

/**
 * Singleton class
 */
class Game {
private:
    static Game *instance;
    Game();
public:
    static Game *getInstance();
    std::array<const Card *, BOARD_SIZE> gameCards;
    //std::stack<State>
};

#endif // GAME_H

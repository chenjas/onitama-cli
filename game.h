#ifndef GAME_H
#define GAME_H

#include <array>
#include <iostream>
#include <stack>
#include "card.h"

#define NUM_CARDS       16
#define NUM_GAME_CARDS  5
#define BOARD_SIZE      5

class Card;
extern std::array<Card, NUM_CARDS> CARDS;

/**
 * Singleton class
 */
class Game {
private:
    static Game *instance;
    Game();
public:
    static Game *getInstance();
    std::array<Card *, BOARD_SIZE> gameCards;
    //std::stack<State>
};

#endif // GAME_H

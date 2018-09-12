#ifndef GAME_H
#define GAME_H

#define NUM_CARDS       16
#define NUM_GAME_CARDS  5

#include <array>
#include <iostream>
#include <stack>
#include <string>
#include "state.h"
#include "card.h"
#include "board.h"

/**
 * Singleton class
 */
class Game {
private:
    static Game *instance;
    Game();
public:
    bool winCondition;
    std::array<const Card *, BOARD_SIZE> gameCards;
    std::stack<State> undoStack, redoStack;

    static Game *getInstance();
    void reset();
    bool tryMove(char, std::string, int, int);
};

#endif // GAME_H

#ifndef GAME_H
#define GAME_H

#include <array>
#include <stack>
#include "card.h"

/**
 * Singleton class
 */
class Game {
private:
    static Game *instance;
    Game();
public:
    static Game *getInstance();
    std::array<Card *, 5> gameCards;
    //std::stack<State>
};

#endif // GAME_H

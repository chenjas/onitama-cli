#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <vector>
#include <string>
#include "game.h"

struct move {
    int rows, cols;
};

using Move = struct move;

class Card {
public:
    std::string name;
    std::vector<Move> moves;
    Card(std::string, std::vector<Move>);
    void render(int, bool=false);
};

#endif // CARD_H

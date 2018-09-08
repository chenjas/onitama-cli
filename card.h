#ifndef CARD_H
#define CARD_H

#include <vector>
#include <string>
#include "game.h"

struct Move {
    int rows, cols;
};

class Card {
public:
    std::string name;
    std::vector<Move> moves;
    Card(std::string, std::vector<Move>);
    std::string render(int, bool=false) const;
};

#endif // CARD_H

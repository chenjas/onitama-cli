#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <vector>
#include <string>

struct move {
    int rows, cols;
};

using Move = struct move;

class Card {
public:
    std::vector<Move> moves;
    std::string name;
    Card(std::string, std::vector<Move>);
    void render(int, bool);
};

#endif // CARD_H

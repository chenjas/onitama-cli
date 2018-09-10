#ifndef CARD_H
#define CARD_H

// Buffered size of each card name
#define NAME_SIZE 9

#include <vector>
#include <string>

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

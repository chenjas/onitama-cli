#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "player.h"

class Board {
public:
    std::array<std::array<const Piece *, 5>, 5> grid;
    Board(Player, Player);
    std::string render(PlayerId);
    bool validMove(int, int, Move);
};

#endif // BOARD_H

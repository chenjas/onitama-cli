#ifndef STATE_H
#define STATE_H

#include "board.h"
#include "player.h"

class State {
public:
    Player player1, player2;
    Board board;
    const Card *nextCard;
    PlayerId currPlayer;
    State(std::array<const Card *, BOARD_SIZE>);
    State(const State&, PieceId, Move);
    std::string render();
};

#endif // STATE_H

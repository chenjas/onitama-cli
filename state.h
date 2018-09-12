#ifndef STATE_H
#define STATE_H

#include "player.h"
#include "board.h"

class State {
public:
    Player player1, player2;
    Board board;
    const Card *nextCard;
    PlayerId currPlayer;

    State(std::array<const Card *, BOARD_SIZE>);
    State(const State&, PieceId, const Card *, Move);
    State(State&&);

    std::string render();
};

#endif // STATE_H

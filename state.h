#ifndef STATE_H
#define STATE_H

#include "board.h"
#include "game.h"
#include "player.h"

class State {
public:
    Player player1, player2;
    Board board;
    const Card *nextCard;
    PlayerId currPlayer;
    State(std::array<const Card *, BOARD_SIZE>);
    State(const State&, PieceId, const Card *, Move);
    std::string render();
    bool validateMove(char, std::string, int, int);
};

#endif // STATE_H

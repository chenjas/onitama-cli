#include "state.h"

using namespace std;

State::State(array<const Card *, BOARD_SIZE> cards):
    player1(PlayerId::P1, cards[0], cards[1]),
    player2(PlayerId::P2, cards[2], cards[3]),
    board(player1, player2),
    nextCard(cards[4]),
    currPlayer(PlayerId::P1)
{}

// Can be called only after the move is validated
State::State(const State& prev, PieceId piece, Move move):
    player1(prev.player1),
    player2(prev.player2),
    board(prev.board),
    nextCard(prev.nextCard)
{
    Player& targetPlayer = (prev.currPlayer == PlayerId::P1) ?
        player1 : player2;

    currPlayer = (prev.currPlayer == PlayerId::P1) ?
        PlayerId::P2 : PlayerId::P1;
}
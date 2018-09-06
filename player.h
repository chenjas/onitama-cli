#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "card.h"

enum PlayerId { P1, P2 };
enum PieceId  { m, p1, p2, p3, p4 };

struct Piece {
    PlayerId player;
    PieceId pieceId;
    int row, col;
    Piece();
    Piece(PlayerId, PieceId, int, int);
};

class Player {
public:
    PlayerId player;
    const Card *card1, *card2;
    Piece *master;
    std::vector<Piece> pawns;
    Player(PlayerId, const Card *, const Card *);
    ~Player();
};

#endif // PLAYER_H

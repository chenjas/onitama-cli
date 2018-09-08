#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "card.h"

enum PlayerId { P1, P2 };
enum PieceId  { p1, p2, p3, p4, m };

struct Piece {
    PlayerId player;
    PieceId pieceId;
    int row, col;
    Piece();
    Piece(PlayerId, PieceId, int, int);
    std::string render(PlayerId) const;
};

class Player {
public:
    PlayerId player;
    const Card *card1, *card2;
    std::vector<Piece> pieces;
    Piece *findPiece(PieceId);
    bool removePiece(PieceId);
    Player(PlayerId, const Card *, const Card *);
    Player(const Player&);
};

#endif // PLAYER_H

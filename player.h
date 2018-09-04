#ifndef PLAYER_H
#define PLAYER_H

enum Player { P1, P2 };
enum Piece  { m, p1, p2, p3, p4 };

struct Piece {
    Player player;
    Piece pieceId;
    int row, col;
};

class Player {

};

#endif // PLAYER_H

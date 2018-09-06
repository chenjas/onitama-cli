#include "player.h"

using namespace std;

Piece::Piece(): player(PlayerId::P1), pieceId(PieceId::m) {}

Piece::Piece(PlayerId p, PieceId pc, int r, int c):
    player(p),
    pieceId(pc),
    row(r),
    col(c) {}

Player::Player(PlayerId p, const Card *c1, const Card *c2):
    player(p),
    card1(c1),
    card2(c2) {

    int row = (p == PlayerId::P1) ? 4 : 0;
    master = new Piece(p, PieceId::m, row, 2);

    pawns.push_back(Piece(p, PieceId::p1, row, 0));
    pawns.push_back(Piece(p, PieceId::p2, row, 1));
    pawns.push_back(Piece(p, PieceId::p3, row, 3));
    pawns.push_back(Piece(p, PieceId::p4, row, 4));
}

Player::~Player() {
    delete master;
}
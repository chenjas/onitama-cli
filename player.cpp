#include "player.h"

using namespace std;

Piece::Piece(): player(PlayerId::P1), pieceId(PieceId::m) {}

Piece::Piece(PlayerId p, PieceId pc, int r, int c):
    player(p),
    pieceId(pc),
    row(r),
    col(c) {}

string Piece::render(PlayerId currPlayer) const {
    if (currPlayer != player)
        return (pieceId == PieceId::m) ? "E" : "e";
    switch (pieceId) {
        case PieceId::m:
            return "M";
        case PieceId::p1:
            return "1";
        case PieceId::p2:
            return "2";
        case PieceId::p3:
            return "3";
        case PieceId::p4:
            return "4";
    }
}

Player::Player(PlayerId p, const Card *c1, const Card *c2):
    player(p),
    card1(c1),
    card2(c2) {

    if (p == PlayerId::P1) {
        master = new Piece(p, PieceId::m, 4, 2);
        pawns.push_back(Piece(p, PieceId::p1, 4, 0));
        pawns.push_back(Piece(p, PieceId::p2, 4, 1));
        pawns.push_back(Piece(p, PieceId::p3, 4, 3));
        pawns.push_back(Piece(p, PieceId::p4, 4, 4));
    } else {
        master = new Piece(p, PieceId::m, 0, 2);
        pawns.push_back(Piece(p, PieceId::p1, 0, 4));
        pawns.push_back(Piece(p, PieceId::p2, 0, 3));
        pawns.push_back(Piece(p, PieceId::p3, 0, 1));
        pawns.push_back(Piece(p, PieceId::p4, 0, 0));
    }
}

Player::~Player() {
    delete master;
}
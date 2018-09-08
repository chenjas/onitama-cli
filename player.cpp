#include "player.h"

using namespace std;

Piece::Piece(): player(PlayerId::P1), pieceId(PieceId::m) {}

Piece::Piece(PlayerId p, PieceId pc, int r, int c):
    player(p),
    pieceId(pc),
    row(r),
    col(c)
{}

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

Piece *Player::findPiece(PieceId pid) {
    for (Piece& p : pieces) {
        if (p.pieceId == pid)
            return &p;
    }
    return nullptr;
}

// Return true if piece removed
bool Player::removePiece(PieceId pid) {
    for (vector<Piece>::iterator i = pieces.begin(); i < pieces.end(); i++) {
        if (i->pieceId == pid) {
            pieces.erase(i);
            return true;
        }
    }
    return false;
}

Player::Player(PlayerId p, const Card *c1, const Card *c2):
    player(p),
    card1(c1),
    card2(c2)
{
    if (p == PlayerId::P1) {
        pieces.push_back(Piece(p, PieceId::p1, 4, 0));
        pieces.push_back(Piece(p, PieceId::p2, 4, 1));
        pieces.push_back(Piece(p, PieceId::m, 4, 2));
        pieces.push_back(Piece(p, PieceId::p3, 4, 3));
        pieces.push_back(Piece(p, PieceId::p4, 4, 4));
    } else {
        pieces.push_back(Piece(p, PieceId::p1, 0, 4));
        pieces.push_back(Piece(p, PieceId::p2, 0, 3));
        pieces.push_back(Piece(p, PieceId::m, 0, 2));
        pieces.push_back(Piece(p, PieceId::p3, 0, 1));
        pieces.push_back(Piece(p, PieceId::p4, 0, 0));
    }
}

Player::Player(const Player& other):
    player(other.player),
    card1(other.card1),
    card2(other.card2),
    pieces(other.pieces)
{}
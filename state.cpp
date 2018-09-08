#include "state.h"

using namespace std;

State::State(array<const Card *, BOARD_SIZE> cards):
    player1(PlayerId::P1, cards[0], cards[1]),
    player2(PlayerId::P2, cards[2], cards[3]),
    board(player1, player2),
    nextCard(cards[4]),
    currPlayer(PlayerId::P1)
{}

/**
 * Precondition: move is a valid, i.e.
 *      move is within bounds,
 *      move complies with chosen card moves
 *      destination square is empty or enemy piece
 */
State::State(const State& prev, PieceId piece, const Card *card, Move move):
    player1(prev.player1),
    player2(prev.player2),
    board(player1, player2),
    nextCard(card)
{
    Player& targetPlayer = (prev.currPlayer == PlayerId::P1) ?
        player1 : player2;
    Player& otherPlayer = (prev.currPlayer == PlayerId::P1) ?
        player2 : player1;

    Piece *src = targetPlayer.findPiece(piece);
    if (!src) {
        cerr << "Piece not found." << endl;
        exit(1);
    }
    int destRow = src->row + move.rows;
    int destCol = src->col + move.cols;

    const Piece*& dest = board.grid[destRow][destCol];
    // Destination should be occupied by other player's piece
    if (dest) {
        bool removed = otherPlayer.removePiece(dest->pieceId);
        if (!removed) {
            cerr << "Piece not removed." << endl;
            exit(1);
        }
    }
    dest = src;
    board.grid[src->row][src->col] = nullptr;
    src->row = destRow;
    src->col = destCol;

    // Swap chosen card with previous state's next card
    if (targetPlayer.card1 == card)
        targetPlayer.card1 = prev.nextCard;
    else
        targetPlayer.card2 = prev.nextCard;

    // Next player's turn
    currPlayer = (prev.currPlayer == PlayerId::P1) ?
        PlayerId::P2 : PlayerId::P1;
}
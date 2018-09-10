#include <algorithm>
#include <cctype>
#include <iostream>
#include "state.h"

using namespace std;

const string BUFFER = "       ";

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

State::State(State&& other):
    player1(other.player1),
    player2(other.player2),
    board(player1, player2)
{
    nextCard = nullptr;
}

string State::render() {
    string currPlayerStr = (currPlayer == PlayerId::P1) ? "P1" : "P2";
    string otherPlayerStr = (currPlayer == PlayerId::P1) ? "P2" : "P1";
    Player& targetPlayer = (currPlayer == PlayerId::P1) ? player1 : player2;
    Player& otherPlayer = (currPlayer == PlayerId::P1) ? player2 : player1;

    string result = "============== " + currPlayerStr + "'s turn ==============\n\n";

    // Render other player's hand
    result += BUFFER + "   " + otherPlayerStr + "'s hand (rotated)\n\n";
    result += BUFFER + otherPlayer.card1->name + BUFFER +
        otherPlayer.card2->name + "\n";
    for (int i = 0; i < BOARD_SIZE; i++) {
        result += BUFFER + otherPlayer.card1->render(i, true) + BUFFER +
            otherPlayer.card2->render(i, true) + "\n";
    }

    // Render board
    result += "\n\n" + board.render(currPlayer) + "\n\n";

    //Render current player's hand
    result += BUFFER + BUFFER + " " + currPlayerStr + "'s hand " + BUFFER +
        BUFFER + BUFFER + "Next card\n\n";
    result += BUFFER + targetPlayer.card1->name + BUFFER +
        targetPlayer.card2->name + BUFFER + BUFFER + nextCard->name + "\n";
    for (int i = 0; i < BOARD_SIZE; i++) {
        result += BUFFER + targetPlayer.card1->render(i) + BUFFER +
            targetPlayer.card2->render(i) + BUFFER + BUFFER +
            nextCard->render(i) + "\n";
    }
    return result;
}

bool State::validateMove(char piece, string cardName, int row, int col) {
    Player& targetPlayer = (currPlayer == PlayerId::P1) ? player1 : player2;

    /* Validate piece */

    PieceId pid;
    switch (tolower(piece)) {
        case '1':
            pid = PieceId::p1;
            break;
        case '2':
            pid = PieceId::p2;
            break;
        case '3':
            pid = PieceId::p3;
            break;
        case '4':
            pid = PieceId::p4;
            break;
        case 'm':
            pid = PieceId::m;
            break;
        default:
            cout << "Invalid piece name." << endl;
            return false;
    }
    Piece *p = targetPlayer.findPiece(pid);
    if (!p) {
        cout << "No such piece on board." << endl;
        return false;
    }

    /* Validate card */

    if (cardName.length() > NAME_SIZE) {
        cout << "Invalid card name." << endl;
        return false;
    }

    // Make card name lower case except first character
    for (char& c: cardName) c = tolower(c);
    cardName[0] = toupper(cardName[0]);

    // Add whitespace buffer to card name
    int cardNameLen = cardName.length();
    for (int i = 0; i < NAME_SIZE - cardNameLen; i++) {
        cardName.push_back(' ');
    }
    if (cardName != targetPlayer.card1->name && cardName != targetPlayer.card2->name) {
        cout << "Invalid card name." << endl;
        return false;
    }
    const Card *card = (cardName == targetPlayer.card1->name) ?
        targetPlayer.card1 : targetPlayer.card2;

    /* Validate move coordinates */

    if (row < 1 || row > 5 || col < 1 || col > 5) {
        cout << "Coordinates out of bounds." << endl;
        return false;
    }

    // Adjust to start from zero
    row--; col--;
    if (currPlayer == PlayerId::P2) {
        // Translations
        row = BOARD_SIZE-1 - row;
        col = BOARD_SIZE-1 - col;
    }

    // Relative coordinates
    int relRow = row - p->row;
    int relCol = col - p->col;

    // Match move in selected card
    bool moveMatch = false;
    for (const Move& m : card->moves) {
        if (currPlayer == PlayerId::P1) {
            if (relRow == m.rows && relCol == m.cols) {
                moveMatch = true;
                break;
            }
        } else { // P2 needs card move translation
            if (relRow == -m.rows && relCol == -m.cols) {
                moveMatch = true;
                break;
            }
        }
    }
    if (!moveMatch) {
        cout << "Invalid move." << endl;
        return false;
    }

    return true;
}

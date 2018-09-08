#include "game.h"
#include "player.h"
#include "board.h"
#include "state.h"

using namespace std;

// All the different cards of Onitama
array<const Card, NUM_CARDS> CARDS = {
    Card("Tiger",
        { {-2,  0}, { 1,  0} }),
    Card("Dragon",
        { {-1, -2}, {-1,  2}, { 1, -1}, { 1,  1} }),
    Card("Frog",
        { {-1, -1}, { 0, -2}, { 1,  1} }),
    Card("Rabbit",
        { {-1,  1}, { 0,  2}, { 1, -1} }),
    Card("Crab",
        { {-1,  0}, { 0, -2}, { 0,  2} }),
    Card("Elephant",
        { {-1, -1}, {-1,  1}, { 0, -1}, { 0,  1} }),
    Card("Goose",
        { {-1, -1}, { 0, -1}, { 0,  1}, { 1,  1} }),
    Card("Rooster",
        { {-1,  1}, { 0, -1}, { 0,  1}, { 1, -1} }),
    Card("Monkey",
        { {-1, -1}, {-1,  1}, { 1, -1}, { 1,  1} }),
    Card("Mantis",
        { {-1, -1}, {-1,  1}, { 1,  0} }),
    Card("Horse",
        { {-1,  0}, { 0, -1}, { 1,  0} }),
    Card("Ox",
        { {-1,  0}, { 0,  1}, { 1,  0} }),
    Card("Crane",
        { {-1,  0}, { 1, -1}, { 1,  1} }),
    Card("Boar",
        { {-1,  0}, { 0, -1}, { 0,  1} }),
    Card("Eel",
        { {-1, -1}, { 0,  1}, { 1, -1} }),
    Card("Cobra",
        { {-1,  1}, { 0, -1}, { 1,  1} })
};

Game *Game::getInstance() {
    if (instance == 0) {
        instance = new Game();
    }
    return instance;
}

Game::Game() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        gameCards[i] = &(CARDS[i]);
    }
    State s1(gameCards);
    cout << s1.board.render(PlayerId::P1) << endl;
    const Card *card = &CARDS[0];
    State s2(s1, PieceId::p2, card, {-4, 0});
    cout << s2.board.render(PlayerId::P2) << endl;

    for (Piece& p: s2.player1.pieces) {
        cout << "id: " << p.pieceId << " row: " << p.row << " col: " << p.col << endl;
    }
    cout << endl;
    for (Piece& p: s2.player2.pieces) {
        cout << "id: " << p.pieceId << " row: " << p.row << " col: " << p.col << endl;
    }
}

Game *Game::instance = 0;

#include "game.h"

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
    // TODO: randomly select cards
    for (int i = 0; i < BOARD_SIZE; i++) {
        gameCards[i] = &(CARDS[i]);
    }

    // Initial state
    undoStack.push(State(gameCards));
    State& top = undoStack.top();
    cout << top.render() << endl;

    //startState.validateMove('1', "Tiger", 3, 1);

    //State s2(startState, PieceId::p1, startState.player1.card1, {-2, 0});
    //cout << s2.render() << endl;
}

Game *Game::instance = 0;

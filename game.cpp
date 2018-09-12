#include <cstdlib>
#include "game.h"

using namespace std;

// All of the unique cards of Onitama
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

Game::Game(): winCondition(false) {}

Game *Game::getInstance() {
    if (instance == 0) {
        instance = new Game();
    }
    return instance;
}

void Game::reset() {
    // Empty the stacks
    while (undoStack.size()) {
        undoStack.pop();
    }
    while (redoStack.size()) {
        redoStack.pop();
    }

    // Select random cards
    //vector<int> indices;
    //for (int i = 0; i < NUM_CARDS; i++) {
    //    indices.push_back(i);
    //}
    //for (int i = 0; i < BOARD_SIZE; i++) {
    //    int randIndex = rand() % indices.size();
    //    gameCards[i] = &(CARDS[indices[randIndex]]);
    //    indices.erase(indices.begin() + randIndex);
    //}
    for (int i = 0; i < NUM_GAME_CARDS; i++) {
        gameCards[i] = &(CARDS[i]);
    }

    // Initial state
    undoStack.push(State(gameCards));
    cout << undoStack.top().render() << endl;

    cout << tryMove('2', "tiger", 3, 2) << endl;
    cout << undoStack.top().render() << endl;

    cout << tryMove('m', "frog", 5, 1) << endl;
    cout << undoStack.top().render() << endl;
}

bool Game::tryMove(char piece, string cardName, int row, int col) {
    if (!undoStack.size()) {
        cerr << "No initial state." << endl;
        exit(1);
    }
    State& currState = undoStack.top();
    Player& targetPlayer = (currState.currPlayer == PlayerId::P1) ?
        currState.player1 : currState.player2;

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
    if (currState.currPlayer == PlayerId::P2) {
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
        if (currState.currPlayer == PlayerId::P1) {
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

    // Check if destination space is occupied by ally piece
    int destRow = p->row + relRow;
    int destCol = p->col + relCol;
    const Piece*& dest = currState.board.grid[destRow][destCol];
    if (dest && dest->player == currState.currPlayer) {
        cout << "Invalid move." << endl;
        return false;
    }

    /* From here, move is valid */

    // Add new state to undostack
    undoStack.push(State(currState, pid, card, { relRow, relCol }));
    // Clear redoStack
    while (redoStack.size()) {
        redoStack.pop();
    }

    return true;
}

Game *Game::instance = 0;

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include "game.h"
#include "player.h"

using namespace std;

const string WELCOME =
    "Welcome to Onitama! Enter the command 'h' at any time for help.";
const string INVALID_CMD = "Invalid command; Enter 'h' for help.";
const string HELP =
    "Enter 'r' to restart, 'q' to quit.\n"
    "The current player's temple arch is always oriented on the bottom of the board.\n"
    "Pieces '1', '2', '3', '4', and 'M' are the pawns and master of the current player.\n"
    "To move, enter the piece name, the specified card name, the destination row,\n"
    "and the destination column, all separated by whitespace and in that precise order.\n"
    "(Example: '1 Tiger 3 5' moves the current player's pawn number 1 to row 3 column 5 "
    "using the 'Tiger' card in his/her hand.)\n"
    "Count rows from top to bottom and columns from left to right, starting at 1.\n"
    "Enter 'undo' or 'redo' to undo and repo moves respectively.";


int main() {
    srand(time(NULL));
    cout << WELCOME << endl << endl;

    Game *game = Game::getInstance();
    game->reset();
    cout << game->renderCurrState() << endl;

    bool exitGame = false;
    while (!exitGame) {
        string input;
        cout << "\nEnter your move: ";
        getline(cin, input);
        cout << endl;
        istringstream iss(input);
        vector<string> tokens(
            istream_iterator<string>{iss}, istream_iterator<string>{}
        );
        if (!tokens.size()) continue;
        if (tokens.size() == 1) {
            if (tokens[0].size() == 1) {
                switch (tokens[0][0]) {
                    case 'r':
                        game->reset();
                        cout << game->renderCurrState() << endl;
                        continue;
                    case 'q':
                        exitGame = true;
                        continue;
                    case 'h':
                        cout << HELP << endl;
                        continue;
                }
            }
            bool result = false;
            if (tokens[0] == "undo") result = game->undo();
            else if (tokens[0] == "redo") result = game->redo();
            if (result) cout << game->renderCurrState() << endl;
            continue;
        }
        if (tokens.size() == 4 && tokens[0].size() == 1 &&
                tokens[2].size() == 1 and tokens[3].size() == 1) {
            char pieceId = tokens[0][0];
            string& cardName = tokens[1];
            int row = tokens[2][0] - '0';
            int col = tokens[3][0] - '0';

            bool result = game->tryMove(pieceId, cardName, row, col);
            if (result) {
                cout << endl << game->renderCurrState() << endl;
                if (game->endState()) {
                    cout << "Press enter to restart. ";
                    getline(cin, input);
                    game->reset();
                    cout << endl << game->renderCurrState() << endl;
                }
            }
            continue;
        }
        cout << "Invalid command." << endl;
    };
    return 0;
}

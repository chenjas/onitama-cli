#include <cstdlib>
#include <ctime>
#include <iostream>
#include "game.h"
#include "player.h"

using namespace std;

int main() {
    srand(time(NULL));
    cout << "Welcome to Onitama! Enter the command 'help' at any time for a list of commands."
         << endl << endl;
    Game *game = Game::getInstance();
    game->reset();
    bool exitGame = false;
    while (!exitGame) {

    };
    return 0;
}

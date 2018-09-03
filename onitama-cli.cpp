#include "game.h"

int main() {
    Game *game = Game::getInstance();
    for (int j = 0; j < NUM_CARDS; j++) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            CARDS[j].render(i);
            std::cout << "\t";
            CARDS[j].render(i, true);
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    return 0;
}

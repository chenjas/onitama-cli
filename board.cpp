#include "board.h"

using namespace std;

Board::Board(Player p1, Player p2): grid{0} {
    for (int i = 0; i < p1.pawns.size(); i++) {
        Piece *pp = &(p1.pawns[i]);
        grid[pp->row][pp->col] = pp;
    }
    for (int i = 0; i < p2.pawns.size(); i++) {
        Piece *pp = &(p2.pawns[i]);
        grid[pp->row][pp->col] = pp;
    }
    if (p1.master) {
        grid[p1.master->row][p1.master->col] = p1.master;
    }
    if (p2.master) {
        grid[p2.master->row][p2.master->col] = p2.master;
    }
}

string Board::render(PlayerId pid) {
    string result = "";
    for (int row = 0; row < BOARD_SIZE; row++) {
        // Each row is 3 lines wide
        for (int line = 0; line < 3; line++) {
            if ((line == 0 && row == 0) ||
                    (line == 2 && row == BOARD_SIZE-1)) {
                result += "       |       | = = = |       |       \n";
            }
            else if (line == 0 || line == 2) {
                result += "       |       |       |       |       \n";
            }
            else {
                result += "       |       |       |       |       \n";
                //for (int col = 0; col < BOARD_SIZE; col++) {
                //    if (pid == PlayerId::P1) {

                //    }
                //    else {

                //    }
                //}
            }
        }
        if (row != BOARD_SIZE-1) {
            result += " - - - + - - - + - - - + - - - + - - - \n";
        }
    }
    return result;
}
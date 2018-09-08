#include "board.h"

using namespace std;

Board::Board(Player& p1, Player& p2): grid{0} {
    for (int i = 0; i < p1.pieces.size(); i++) {
        Piece *pp = &(p1.pieces[i]);
        grid[pp->row][pp->col] = pp;
    }
    for (int i = 0; i < p2.pieces.size(); i++) {
        Piece *pp = &(p2.pieces[i]);
        grid[pp->row][pp->col] = pp;
    }
}

string Board::render(PlayerId currPlayer) {
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
                for (int col = 0; col < BOARD_SIZE; col++) {
                    const Piece *pp ;
                    if (currPlayer == PlayerId::P1) {
                        pp = grid[row][col];
                    } else {
                        pp = grid[BOARD_SIZE-1 - row][BOARD_SIZE-1 - col];
                    }
                    if (pp) {
                        result += "   " + pp->render(currPlayer) + "   ";
                    } else {
                        result += "       ";
                    }
                    if (col < BOARD_SIZE-1) result += "|";
                }
                result += "\n";
            }
        }
        if (row != BOARD_SIZE-1) {
            result += " - - - + - - - + - - - + - - - + - - - \n";
        }
    }
    return result;
}
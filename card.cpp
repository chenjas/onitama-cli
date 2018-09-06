#include "card.h"

using namespace std;

Card::Card(string n, vector<Move> m) {
    name = n;
    moves = m;
}

string Card::render(int row, bool rotated) {
    string result = "";
    for (int col = 0; col < BOARD_SIZE; col++) {
        if (row == 2 && col == 2) {
            result += "# ";
            continue;
        }
        bool moveMatch = false;
        for (Move m : moves) {
            int mRows, mCols;
            if (rotated) {
                mRows = -m.rows; mCols = -m.cols;
            } else {
                mRows = m.rows; mCols = m.cols;
            }
            if (mRows == row - 2 && mCols == col - 2) {
                moveMatch = true;
                break;
            }
        }
        result += (moveMatch ? "@" : ".");
        if (col < BOARD_SIZE - 1) result += " ";
    }
    return result;
}

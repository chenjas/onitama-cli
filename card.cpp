#include "card.h"

using namespace std;

Card::Card(string n, vector<Move> m) {
    moves = m;
    name = n;
}

void Card::render(int row, bool rotated=false) {

}

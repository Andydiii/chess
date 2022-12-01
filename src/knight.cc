#include "knight.h"
#include "board.h"

using namespace std;

Knight::Knight(int row, int col, string team, bool undercap, bool moved):
    Piece{row, col, team, "knight", undercap, moved, false}
{}


bool Knight::validmove(Board &board, int *dest, bool suicide, bool &canCheck, bool &captureEnemy, bool &escape) {
    Piece *destpiece = board.theBoard[dest[0]][dest[1]];
    if (!(0 <= dest[0] && dest[0] < 8 && 0 <= dest[1] && dest[1] < 8) || (destpiece != nullptr && destpiece->getTeam() == team)) {
        // dest is: out of bounds, same team (if dest==pos, team will be same)
        return false;
    }
    // if dest has a piece, then it's guranteed to be different team!!!!!!!!!!

    // check for valid knight squares
    if ((abs(dest[0] - pos[0]) == 2 && abs(dest[1] - pos[1]) == 1) || (abs(dest[0] - pos[0]) == 1 && abs(dest[1] - pos[1]) == 2)) {
        // dest guranteed to be empty OR enemy piece
        if (suicide) {
            captureEnemy = true;
            return true;
        } else {
            Board *nb = moveto(board, dest);
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    Piece *p = nb->theBoard[i][j];
                    if (p != nullptr && p->getTeam() == team && p->getType() == "king") {
                        if (p->getUndercheck(*nb)) {
                            delete nb;
                            return false;
                        } else {
                            delete nb;
                            return true;
                        }
                    }
                }
            }
        }
    } else {
        // not valid knight move
        return false;
    }
}

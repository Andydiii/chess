#include "bishop.h"
#include "board.h"

using namespace std;

Bishop::Bishop(int row, int col, string team, bool undercap, bool moved):
    Piece{row, col, team, "bishop", undercap, moved, false}
{}


bool Bishop::validmove(Board &board, int *dest, bool suicide, bool &canCheck, bool &captureEnemy, bool &escape) {
    Piece *destpiece = board.theBoard[dest[0]][dest[1]];
    if (!(0 <= dest[0] && dest[0] < 8 && 0 <= dest[1] && dest[1] < 8) || (destpiece != nullptr && destpiece->getTeam() == team)) {
        // dest is: out of bounds, same team (if dest==pos, team will be same)
        return false;
    }
    // if dest has a piece, then it's guranteed to be different team!!!!!!!!!!
    
    // check that all pieces in the middle (except start and dest) are nullptrs
    if (abs((dest[0] - pos[0])) == abs((dest[1] - pos[1]))) {
        // moving diagonal
        // gap > 0 gurantee, if gap==0, then dest.team==cur.team would return false at start
        int gap = abs(dest[0] - pos[0]);

        if ((dest[0] > pos[0]) && (dest[1] > pos[1])) {
            // diagonal up right
            for (int i = 1; i < gap; i++) {
                if (board.theBoard[pos[0] + i][pos[1] + i] != nullptr) {
                    return false;
                }
            }
        } else if ((dest[0] > pos[0]) && (dest[1] < pos[1])) {
            // diagonal up left
            for (int i = 1; i < gap; i++) {
                if (board.theBoard[pos[0] + i][pos[1] - i] != nullptr) {
                    return false;
                }
            }
        } else if ((dest[0] < pos[0]) && (dest[1] > pos[1])) {
            // diagonal down right
            for (int i = 1; i < gap; i++) {
                if (board.theBoard[pos[0] - i][pos[1] + i] != nullptr) {
                    return false;
                }
            }
        } else {
            // diagonal down left
            for (int i = 1; i < gap; i++) {
                if (board.theBoard[pos[0] - i][pos[1] - i] != nullptr) {
                    return false;
                }
            }
        }
    } else {
        // not diagonal
        return false;
    }
    // already checked that move is diagonal, and no pieces between pos and dest
    // also, if dest has a piece, it is guranteed to be enemy piece

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
}

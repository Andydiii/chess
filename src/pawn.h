#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn: public Piece {
    // bool hasMoved;
    bool enpassant;
public:
    Pawn(int row, int col, std::string team, bool undercap, bool moved);
    bool validmove(Board &board, int *dest, bool suicide, bool &canCheck, bool &captureEnemy, bool &escape) override;
    bool getUndercheck(Board &board) override;
    // virtual bool canEnpassant(Board &board, int *dest) override;
    bool enpassant(Board &board, int *dest);
};

#endif

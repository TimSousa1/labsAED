#ifndef BOARD_H
#define BOARD_H

typedef struct _board Board;

Board* initBoard (int, int);
Board* copyBoard (Board*, int, int);
void   placeQueenBoard(Board*, int*, int);
void   deleteBoard (Board *, int, int);
void   printBoard (Board*, int, int);
int    allQueensPlaced(Board *, int);
void   invalidatePlay(Board *, int, int, int*, int);
int    isBoardPositionAvailable(Board*, int , int);
int    thereisHope(Board *, int, int, int);
void   boardLastPlay(Board*, int*);
void   boardSetLastPlay(Board*, int*);

#define QUEEN 1
#define AVAILABLE 0

#endif

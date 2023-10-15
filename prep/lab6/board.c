#include <stdio.h>
#include <stdlib.h>

#include "board.h"

struct _board{
  int **board;
  int play[2];      /* queen placement that led to this board been created */
  int lastplay[2];  /* last play; this could also be a list of possible plays */
  int ctr_free;
  int queensPlaced; /* how many queens are placed on this baord */
};


/*****************************************************************************
 * initBoard ()
 *
 * Arguments: L, C - the board dimensions
 *
 * Returns: board - the allocated board structure
 * Side-Effects: table is allocated in place
 *
 * Description: allocates the matrix "board"
 *              structure
 *                   board: game's board
 *
 ****************************************************************************/

Board* initBoard(int L, int C){
  int i;
  Board *b = NULL;

  /* allocate initial game board structure */
  b = (Board*) malloc(sizeof(Board));
  if(b == NULL) {
    perror("Failed to allocate memory for the boards!\n");
    exit(EXIT_FAILURE);
  }

  /* now allocate the actual board, just an L x C matrix */
  b->board = (int**) malloc(L*sizeof(int*));
  if(b->board == NULL) {
    perror("Failed to allocate memory for the boards!\n");
    exit(EXIT_FAILURE);
  }
  for (i = 0; i < L; i++){
    b->board[i] = (int*) calloc(C,sizeof(int));
    if(b->board[i] == NULL) {
      perror("Failed to allocate memory for the boards!\n");
      exit(EXIT_FAILURE);
    }
  }
  /* there is no last play yet */
  b->lastplay[0] = 0;
  b->lastplay[1] = 0;
  b->ctr_free = L * C;
  b->queensPlaced=0;

  return b;
}



/******************************************************************************
 * placeQueenBoard ()
 *
 * Arguments: b - board structure
 *            play - coordinates where to place queen
 *            piece - queen to be placed in given coordinates
 *
 * Returns: (void)
 * Side-Effects: new queen is placed in board
 *
 * Description: places a queen in the coordinates provided
 *
 *****************************************************************************/

void placeQueenBoard(Board *b, int play[], int piece) {
  int line = play[0], col = play[1];

  b->board[line][col] = piece;
  b->play[0] = line;
  b->play[1] = col;
  b->lastplay[0] = 0;
  b->lastplay[1] = 0;
  b->queensPlaced++;

  return;
}


/******************************************************************************
 * allQueensPlaced ()
 *
 * Arguments: b - board structure
 *            targetQueens - target queens to be placed
 *
 * Returns: boolean indicating success in placing all queens
 * Side-Effects: (none)
 *
 * Description: checks if all queens have been placed
 *
 *****************************************************************************/

int allQueensPlaced(Board *b, int targetQueens) {
  return (b->queensPlaced == targetQueens);
}


/******************************************************************************
 * copyBoard ()
 *
 * Arguments: original - board structure with table to copy
 *            L, C - board dimensions
 *
 * Returns: copy - the new board, copy of the original
 * Side-Effects: a new board structure is allocated; table is copied in place
 *
 * Description: copies the board "original" to the board "copy" which is
 *              allocated in the function; copies all relevant fields of board
 *              structure
 *
 *****************************************************************************/

Board* copyBoard(Board *original, int L, int C){
  int i, j;
  Board *copy;

  /***************************************************************************

  COMPLETAR: allocar um board novo e copiar o board original para ele
               copiando todos os campos relevantes

  ***************************************************************************/

  copy = initBoard(L, C);

  for (i = 0; i < L; i++) {
    for (j = 0; j < C; j++) {
      copy->board[i][j] = original->board[i][j];
    }
  }
  copy->play[0] = original->play[0];
  copy->play[1] = original->play[1];
  copy->lastplay[0] = original->lastplay[0];
  copy->lastplay[1] = original->lastplay[1];
  copy->ctr_free = original->ctr_free;
  copy->queensPlaced = original->queensPlaced;

  return copy;
}


/******************************************************************************
 * deleteBoard ()
 *
 * Arguments: b - board structure with tables to delete
 *            L, C - board dimensions
 *
 * Returns: (void)
 * Side-Effects: table is freed
 *
 * Description: frees the table "board" of the input structure; frees all
 *              fields that were dynamically allocated
 *
 *****************************************************************************/

void deleteBoard(Board *b, int L, int C){
  int i;

  for (i = 0; i < L; i++){
    free(b->board[i]);
  }
  free(b->board);

  free(b);
}


/******************************************************************************
 * printBoard ()
 *
 * Arguments: b - board structure with tables to delete
 *            L, C - board dimensions
 *
 * Returns: (void)
 * Side-Effects: (none)
 *
 * Description: prints the table "board"
 *
 *****************************************************************************/

void printBoard(Board *b, int L, int C){
  int i=0, j=0;

  for (i = 0; i < L; i++){
    for (j = 0; j < C; j++){
      if(b->board[i][j] > 0)
        printf("Q ");
      else if(b->board[i][j] == AVAILABLE)
        printf(". ");
      else
        printf("%2d", b->board[i][j]);
    }
    printf("\n");
  }

  return;
}


/******************************************************************************
 * invalidatePlay ()
 *
 * Arguments: b - board structure
 *            L, C - board dimensions
 *            play - play that was made in this board (queen placement)
 *            numplay - play number (in seuence of plays)
 *
 * Returns: (void)
 * Side-Effects: board locations in the same row, column or diagonals of
 *               last play location cannot be used for further queen placement
 *
 * Description: invalidates locations in the same row, column or diagonals of
 *              last play location; these cannot be used for further queen
 *              placement
 *
 *****************************************************************************/

void invalidatePlay(Board* b, int L, int C, int play[], int numplay) {
  int i, j, line = play[0], col = play[1];

  /* Mark the entire row and column as blocked */
  for (i = 0; i < L; i++) {
    if (b->board[i][col] == 0)
      b->board[i][col] = -numplay; /* Mark column */
    if (b->board[line][i] == 0)
      b->board[line][i] = -numplay; /* Mark row */
  }

  /* Mark diagonals */
  for (i = line + 1, j = col + 1; i < L && j < C; i++, j++) {
    if (b->board[i][j] == 0)
      b->board[i][j] = -numplay; /* Mark bottom-right diagonal */
  }

  for (i = line - 1, j = col + 1; i >= 0 && j < C; i--, j++) {
    if (b->board[i][j] == 0)
      b->board[i][j] = -numplay; /* Mark bottom-right diagonal */
  }

  for (i = line + 1, j = col - 1; i < L && j >= 0; i++, j--) {
    if (b->board[i][j] == 0)
      b->board[i][j] = -numplay; /* Mark bottom-right diagonal */
  }

  for (i = line - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
    if (b->board[i][j] == 0)
      b->board[i][j] = -numplay; /* Mark bottom-right diagonal */
  }
}


/******************************************************************************
 * isBoardPositionAvailable ()
 *
 * Arguments: b - board structure
 *            i, j - location/position to be checked
 *
 * Returns: true if position sought is not marked as occupied or invalid
 * Side-Effects: (none)
 *
 * Description: checks to see if a given position is not marked as occupied
 *              or invalid
 *
 *****************************************************************************/

int isBoardPositionAvailable(Board* b, int i, int j) {
  return(b->board[i][j] == AVAILABLE);
}


/******************************************************************************
 * thereisHope ()
 *
 * Arguments: b - board structure
 *            L, C - board dimensions
 *            T - number of queens to placed in game
 *
 * Returns: true if there are still sufficient open positions to place the
 *          remaining queens
 * Side-Effects: counter of free positions is updated
 *
 * Description: checks to see if the number of available positions in the
 *              board, i.e., positions neither occupied nor marked as invalid,
 *              is larger than the number of queens yet to be placed
 *
 *              In more complex games this function can be made smarter and
 *              perform additional checks but the main ideas remains: we
 *              want to estimate if it is worthwhile to continue exploring
 *              the current sequence of moves; if we can determine that we
 *              cannot reach our goal by continuing on this path, then we
 *              should give up and try a different sequence
 *
 *****************************************************************************/

int thereisHope(Board *b, int L, int C, int T){
  int i, j;

  /* Check the entire board */
  b->ctr_free = 0;
  for (i = 0; i < L; i++)
    for (j = 0; j < C; j++)
      if (b->board[i][j] == AVAILABLE)
        b->ctr_free++;
  if (b->ctr_free >= (T - b->queensPlaced))
    return 1;
  else
    return 0;
}


/******************************************************************************
 * boardLastPlay ()
 *
 * Arguments: b - board structure with tables
 *            curplay - array for last play information
 *
 * Returns: curplay - coordinates for last play attempted
 * Side-Effects: (none)
 *
 * Description: checks to see if a given position is not marked as occupied
 *              or invalid
 *
 *****************************************************************************/

void  boardLastPlay(Board *b, int *curplay) {
  curplay[0] = b->lastplay[0];
  curplay[1] = b->lastplay[1];

  return;
}


/******************************************************************************
 * boardSetLastPlay ()
 *
 * Arguments: b - board structure with tables
 *            lastplayplay - array for last play information
 *
 * Returns: (none)
 * Side-Effects: lastplay gets recorded
 *
 * Description: recorded where last play was attempted; this is used as the
 *              staring point to find the next possible play/move
 *
 *****************************************************************************/

void  boardSetLastPlay(Board *b, int *lastplay) {
  b->lastplay[0] = lastplay[0];
  b->lastplay[1] = lastplay[1];

  return;
}

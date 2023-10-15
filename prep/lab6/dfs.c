/* DFS algorithm in C */

#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "board.h"
#include "dfs.h"


#define max(a,b) (a > b ? a : b);


/*****************************************************************************
 * makeBoardMove ()
 *
 * Arguments: b - the board structure
 *            L, C - the board dimensions
 *            play - play to be made
 *            number of play
 *
 * Returns: board - a new, allocated board structure, including the move
 * Side-Effects: table is allocated and move is executed
 *
 * Description: allocates a copy of the board and make the move in it
 *
 ****************************************************************************/

Board* makeBoardMove (Board *board, int L, int C, int play[], int numplay){
  Board *newboard=NULL;

  newboard = copyBoard(board, L, C);
  placeQueenBoard(newboard, play, QUEEN);
  invalidatePlay(newboard, L, C, play, numplay);

  return newboard;
}


/*****************************************************************************
 * getNewBoardMove ()
 *
 * Arguments: b - the board structure
 *            L, C - the board dimensions
 *            newplay - play/move to be made
 *
 * Returns: success of not
 * Side-Effects: new move is filled in and returned
 *
 * Description: starting from the location of the last attempted move,
 *              tries to find a new move
 *
 ****************************************************************************/

int getNewBoardMove(Board *b, int L, int C, int newplay[]) {
  int i, j, lastplay[2];
  int success = 0;

  boardLastPlay(b, lastplay);

  for (i = lastplay[0]; i < L; i++) {
    for (j = 0; j < C; j++) {
      if (i == lastplay[0] && j <= lastplay[1])
        continue;
      if (isBoardPositionAvailable(b, i, j)) {
        success = 1;
        newplay[0] = i;
        newplay[1] = j;
        break;
      }
    }
    if (success == 1)
      break;
  }

  return success;
}


/*****************************************************************************
 * DFS ()
 *
 * Arguments: b - the board structure
 *            L, C - the board dimensions
 *            l0, c0 - coordinates for placement of first queen
 *            T - target number of queens to place
 *
 * Returns: filed in board if successfull, NULL otherwise
 * Side-Effects: lots...
 *
 * Description: uses DFS working on conceptual game tree to find a solution
 *              to the T queens game on the given LxC board with first queen
 *              initially placed at (l0,c0)
 *
 ****************************************************************************/

Board* DFS(Board *b, int L, int C, int l0, int c0, int T) {
  Stack *stack = createStack(T);
  int numplay = 1;
  Board *currentBoard;
  int play[2] = {l0, c0};
  int thereArePlaysToMake = 1;

  /* now do the initial play; place queen at (lo,c0) */
  currentBoard = makeBoardMove(b, L, C, play, numplay);
  push(stack, (Item) currentBoard);

  while(1) {

    currentBoard = (Board*)pop(stack);
    if (currentBoard == NULL) break;
    /* still need to place a few more queens, assume it is possible */
    while (1) {

      /* did we already place all queens */
      if(allQueensPlaced(currentBoard, T)) { //we found the solution
        for (; numplay > 1; numplay--) {
          deleteBoard(pop(stack), L, C);
        }
        deleteStack(stack);
        return currentBoard;
      }

      /* check for potential new plays */
      thereArePlaysToMake = getNewBoardMove(currentBoard, L, C, play);

      if(thereArePlaysToMake == 0) {
        /* there were no more plays available, but we know we are not done */
        numplay--;
        /* back to the previous board */

  /***************************************************************************

    COMPLETAR: neste board não há mais jogadas possíveis, temos de voltar
               atrás e tentar outra sequência de jogadas
               mas convém deixar tudo "limpinho"

  ***************************************************************************/
        deleteBoard(currentBoard, L, C);
        break;

      } else {
        /* there are plays to make, should we? */
        if(!thereisHope(currentBoard, L, C, T)){
          /* Don't follow this branch! No longer hope for it */
          numplay--;
          /* back to the previous board */

  /***************************************************************************

    COMPLETAR: neste board não há mais jogadas possíveis, temos de voltar
               atrás e tentar outra sequência de jogadas
               mas convém deixar tudo "limpinho"

  ***************************************************************************/
          deleteBoard(currentBoard, L, C);
          break;

        } else {
          /* make the play whose info is in play[] */
          numplay++;

  /***************************************************************************

    COMPLETAR: jogada parece boa, vamos fazê-la e continuar a tentar

  ***************************************************************************/
          boardSetLastPlay(currentBoard, play);
          push(stack, (Item) currentBoard);
          currentBoard = makeBoardMove(currentBoard, L, C, play, numplay);
        }
      }

    }

  }
  deleteStack(stack);
  return NULL;
}

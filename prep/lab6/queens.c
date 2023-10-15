#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "dfs.h"



/*****************************************************************************
 * help ()
 *
 * Arguments: (none)
 *
 * Returns: (none)
 * Side-Effects: (none)
 *
 * Description: displays help message
 *
 ****************************************************************************/

void help(){
    printf("usage: ./queens <L> <C> <l0> <c0> <T>\n");
    printf("------------------------------------------------------\n");
    printf("\t\tL: Number of lines in the board [ L >= 1 ]\n");
    printf("\t\tC: Number of lines in the board [ C >= 1 ]\n");
    printf("\t\tl0: Line where the first queen is located [0 <= l0 < L]\n");
    printf("\t\tc0: Column where the first queen is located [ 0 <= c0 < C ]\n");
    printf("\t\tT: Number of subsequent queens to place [ T > 0 ]\n");
    printf("------------------------------------------------------\n");
}



/*****************************************************************************
 * main ()
 *
 * Arguments: argc, argv
 *
 * Returns: success or not whether it was able to place T queens on board
 * Side-Effects: (none)
 *
 * Description: N queens game, receives board size LxC, position (l0,c0) of
 *               first queen placement and T target number of queens to place
 *
 ****************************************************************************/

int main(int argc, char *argv[]){
  Board *board, *solution;
  int L, C, l0, c0, T;

  /* deal with input arguments */
  if (argc != 6){
    help();
    exit(0);
  }
  /* read board dimensions */
  if(((L = atoi(argv[1])) < 1) || ((C = atoi(argv[2])) < 1)){
    /* invalid board dimensions */
    help();
    exit(0);
  }

  /* now read initial queen position */
  if (((l0 = atoi(argv[3])) < 0) || (l0 > L) ||
      ((c0 = atoi(argv[4])) < 0) || (c0 > C)) {
    /* invalid first queen coordinates */
    help();
    exit(0);
  }

  /* now read how many queens we want to place */
  if ((T = atoi(argv[5])) < 0){
    help();
    exit(0);
  }

  /* initialize board */
  board = initBoard(L, C);

  /* try to place the remaining T-1 queens */
  solution = DFS(board, L, C, l0, c0, T);

  if (solution != (Board*)NULL) {
    printf("Success, all T queens place:\n");
    printBoard(solution, L, C);
    deleteBoard(solution, L, C);
  } else {
    printf("Unsuccessful: could not place all T queens on board\n");
  }

  /*****************************************************************

   COMPLETAR: de forma a que a execucao com valgrind esteja limpa 

   *****************************************************************/

  deleteBoard(board, L, C);

  return 0;
}

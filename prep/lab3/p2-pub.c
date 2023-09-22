/******************************************************************************
 *
 * File Name: p2-pub.c
 *	      (c) 2023 AED
 * Author:    AED Team
 * Revision:  20 Sep 2023
 *
 * NAME
 *     p2-pub.c - memory management simulator
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *     #include <ctype.h>
 *
 * DESCRIPTION
 *
 *
 * DIAGNOSTICS
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "memmgt.h"

int main(void)
{
  int ret, val = 0, done=0;
  char cmd = 0, line[128];

  do {
    (void) fgets(line, 128, stdin);
    ret = sscanf(line, "%c %d", &cmd, &val);

    if(ret != 2 || cmd != 'M' || val <= 0) fprintf ( stdout, "-3\n");

  } while (ret != 2 || cmd != 'M' || val <= 0);
  /* waits for command for initializing memory*/

  startMemoryManager(val);

  /* main loop of the simulator */
  while (!done) {

    do {
      (void) fgets(line, 128, stdin);
      ret = sscanf(line, "%c %d", &cmd, &val);
    } while (ret != 2);

    switch (toupper(cmd)) {

    case 'R':
      /* allocation request */
      if(val < 0) {
        fprintf(stderr, "-3\n");
        break;
      }

      /* 'R 0' exits the program */
      if(val == 0) {
        done = 1;
        break;
      }

      /* memory allocation */
      ret = myMalloc(val);
      if (ret == -1)
        fprintf ( stdout, "%d\n", ret);
      else
        fprintf ( stdout, "%d %d\n", val, ret);

      break;

    case 'F':
      /* memory free request */
      if(val < 0) {
        fprintf(stderr, "-3\n");
        break;
      }

      /* free memory */
      ret = myFree(val);
      if (ret == -2)
        fprintf ( stdout, "%d\n", ret);
      else
        fprintf ( stdout, "%d %d\n", ret, val);

      break;

    case 'S':
      /* show current state of memory */
      showMemory();
      break;

    case 'Z':
      /* implement my own function */
      ret = myMemFunc();
      break;

    default:
      fprintf(stderr, "-3\n");
    }
  }

  /* show memory state just before leaving */
  showMemory();

  /* COMPLETAR: libertar toda a memoria e fechar o simulador */;

  return 0;
}

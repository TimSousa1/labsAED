#ifndef DFS_H
#define DFS_H

#include "board.h"
#include "stack.h"

typedef struct _stacknode StackNode;

void     freePlay();
Board*   fazLance(Board*, int, int, int*, int);
int      geraNovoLance(Board*, int, int, int*);
int      thereisHope(Board*, int, int, int);
Board*   DFS(Board *, int, int, int, int, int);

#endif

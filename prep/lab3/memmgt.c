/******************************************************************************
 *
 * File Name: memmgt.c
 *	      (c) 2023 AED
 * Author:    AED Team
 * Revision:  20 Sep 2023
 *
 * NAME
 *     memmgt.h - memory management
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *     #include "memmgt.h"
 *
 * DESCRIPTION
 *
 *
 * DIAGNOSTICS
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>

#include "memmgt.h"

/* possible states of memory blocks */
typedef enum {ALLOC, FREE} mem_state;

/* define basic element of memory management Linked list  */
typedef struct _t_memory {
    int address;
    int size;
    mem_state state;
    struct _t_memory *next;
} t_memory;

/* head of memory management Linked list */
t_memory* memoryLst = NULL;


/******************************************************************************
 * startMemoryManager()
 *
 * Arguments: size (int)     - size of total memory
 * Returns: (none)
 * Side-Effects: memory management list gets initialized with total memory
 *
 * Description: Function for initializing the memory management system by
 *                allocating a memory block representing the full memory
 *                available
 *
 *****************************************************************************/

void startMemoryManager(int size) {

    /* allocate system memory; recall we have a function to allocate a block */
    memoryLst = (t_memory*) malloc (sizeof(t_memory));

    memoryLst->address = 0;
    memoryLst->size = size;
    memoryLst->state = FREE;

    memoryLst->next = NULL;

    return;
}


/******************************************************************************
 * newMemoryBlock()
 *
 * Arguments: address (int)  - address where the block was allocated
 *            size (int)     - size of block
 *            mem_state      - state of the memory block, allocated or free
 * Returns: pointer to newly allocated block
 * Side-Effects: one more block gets allocated
 *               no effects on existing data structures
 *
 * Description: Function for allocating a new memory block
 *
 *****************************************************************************/

t_memory* newMemoryBlock(int address, int size, mem_state state) {

    t_memory *block;

    /* allocate a block of a given size and return a pointer to it */

    block = (t_memory*) malloc (sizeof(t_memory)); /* COMPLETAR: codigo de alocacao de memoria */

    if (!block) exit(EXIT_FAILURE);

    block->address = address;
    block->size = size;
    block->state = state;

    return block;
}


/******************************************************************************
 * closeMemoryManager()
 *
 * Arguments: (none)
 * Returns: (none)
 * Side-Effects: clear all info in memory management list and frees all memory
 *
 * Description: Function for clearing all data in the memory management system
 *                and freeing all memory used by the system itself
 *                (not to be confused by the action of freeing the blocks
 *                marked as allocated in the system)
 *
 *****************************************************************************/

void closeMemoryManager() {

    /* COMPLETAR: codigo para libertacao da lista de blocos */

    /* Memory blocks list is accessiblethrough memoryLst */

    return;
}


/******************************************************************************
 * myMalloc()
 *
 * Arguments: size  (int)  - size of requested memory block
 * Returns: address where block was allocated in the existing memory
 * Side-Effects: if the function is successfull, a new block is allocated
 *               and the memory management list is changed accordingly
 * Description: memory allocation algorithm
 *
 *****************************************************************************/

int myMalloc(int size) {

    int address = -1;  /* default is the allocation was not successfull */
    t_memory *find, *prev, *alloc;

    for (find = memoryLst; find; find = find->next){
        if (find->size >= size && find->state == FREE){
            if (find->size > size) {
                alloc = find->next;
                find->next = newMemoryBlock(find->address + size, find->size - size, find->state);
                find->next->next = alloc;
                find->size = size;
            }
            address = find->address;
            find->state = ALLOC;
            break;
        }

        /* COMPLETAR: implementacao do algoritmo de alocacao de memoria
         * pedido no enunciado lembrar necessidade de tratamento diferenciado
         * para o primeiro da lista, para um elemento qualquer da lista e
         * possivelmente para o último
         */
    }

    return address;
}


    /******************************************************************************
     * myFree()
     *
     * Arguments: address (int)  - address where the block was allocated
     * Returns: size of block that was just freed
     * Side-Effects: if the function is successfull, a block previously
     *               allocated in address is now returned; the block may be merged
     *               with the block before it and after it, therefore the list
     *               could be changed
     * Description: memory allocation algorithm
     *
     *****************************************************************************/

int myFree(int address) {

    int size;
    t_memory *find, *previous = NULL;

    find = memoryLst;

    /* Procura um bloco alocado no endereço 'address' */
    while(find != NULL) {

        if (find->address == address && find->state == ALLOC) break;

        previous = find;
        find = find -> next;
    }

    /* Retorna erro se nao encontrar*/
    if (find == NULL) return -2;

    /* Liberta bloco se encontrar */

    /* COMPLETAR: implementacao do algoritmo de libertacao de memoria
     * pedido no enunciado lembrar necessidade de tratamento diferenciado
     * para o primeiro da lista, para um elemento qualquer da lista e
     * possivelmente para o último
     */

    /* COMPLETAR: adicionar código para fundir blocos
     * livres adjacentes ao libertado se necessário
     */

    return size;
}


/******************************************************************************
 * showMemory()
 *
 * Arguments: (none)
 * Returns: (none)
 * Side-Effects: (none)
 * Description: shows the status of all memory blocks, allocated and free
 *
 *****************************************************************************/

void showMemory() {

    t_memory* find;

    find = memoryLst;

    /* COMPLETAR: percorre lista e mostra estado de todos os blocos */

    return;
}


/******************************************************************************
 * myMemFunc()
 *
 * Arguments: (none)
 * Returns: int
 * Side-Effects: (none)
 * Description: do what is required
 *
 *****************************************************************************/

int myMemFunc() {
    int ret = 0;

    /* do something */

    return (ret);
}

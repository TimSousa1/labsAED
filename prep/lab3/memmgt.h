/******************************************************************************
 *
 * File Name: memmgt.h
 *	      (c) 2023 AED
 * Author:    AED Team
 * Revision:  20 Sep 2023
 *	      (c) 2017 AED
 *
 * NAME
 *     memmgt.h - memory management
 *
 * SYNOPSIS
 *     #include <stdio.h>
 *     #include <stdlib.h>
 *
 * DESCRIPTION
 *
 *
 * DIAGNOSTICS
 *
 *****************************************************************************/


#ifndef _MEMMGT_H
#define _MEMMGT_H

#include <stdio.h>
#include <stdlib.h>

void startMemoryManager(int size);
void closeMemoryManager();
int myMalloc(int size);
int myFree(int address);
void showMemory();
int myMemFunc();

#endif

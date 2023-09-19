/******************************************************************************
 * (c) 2010-2019 AED Team
 * Last modified: abl 2019-02-22
 *
 * NAME
 *   connectivity.c
 *
 * DESCRIPTION
 *   Algorithms for solving the connectivity problem -  QF QU WQU CWQU
 *   For each method count number of entry pairs and the number of links
 *
 * COMMENTS
 *   Code for public distribution
 ******************************************************************************/
#include<stdio.h>
#include<stdlib.h>

#include "connectivity.h"

#define DEBUG 0

/******************************************************************************
 * quick_find()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Quick Find algorithm
 *****************************************************************************/

void quick_find(int *id, int N, FILE * fp, int quietOut)
{
    int i, p, q, t;

    int pairs_cnt = 0;            /* connection pairs counter */
    int links_cnt = 0;            /* number of links counter */

    ulong find_operations_cnt = 0;
    ulong union_operations_cnt = 0;

    int trees = 0, skip;
    int *alreadyRead = NULL;

    ulong complexity_cnt = 0;
    /* initialize; all disconnected */
    for (i = 0; i < N; i++)
        id[i] = i;

    /* read while there is data */
    while (fscanf(fp, "%d %d", &p, &q) == 2) {
        pairs_cnt++;
        /* do search first */
        find_operations_cnt += 2;
        if (id[p] == id[q]) {
            /* already in the same set; discard */
#if DEBUG
            printf("\t%d %d\n", p, q);
#endif
            continue;
        }

        /* pair has new info; must perform union */
        union_operations_cnt++;
        for (t = id[p], i = 0; i < N; i++, union_operations_cnt++) {
            if (id[i] == t) {
                id[i] = id[q];
                union_operations_cnt += 2;
            }
        }

        links_cnt++;
        if (!quietOut)
            printf(" %d %d\n", p, q);
    }

    printf("\n"); 
    for (i = 0; i < N; i++) {
        skip = 0;
        if (trees > 0){
            for (t = 0; t < trees; t++) {
                if (id[i] == alreadyRead[t]) skip = 1;
                complexity_cnt++;
            }
        }
        if (skip) continue;
        printf("%d", i);
        for (t = i + 1; t < N; t++) {
            if (id[i] == id[t]) printf("-%d", t);
            complexity_cnt += 2;
        }
        printf("\n");

        trees++;

        if (!alreadyRead) alreadyRead = (int *) malloc(sizeof(int));
        else alreadyRead = (int *) realloc(alreadyRead, trees * sizeof(int));

        alreadyRead[trees - 1] = id[i];
    }
    free(alreadyRead);
    
    printf("Number of sets: %d\n", trees);
    printf("QF: The number of links performed is %d for %d input pairs.\n",
            links_cnt, pairs_cnt);
    printf("QF: The number of elementary operations performed is %lu when searching, %lu when performing union, with a total of %lu for %d input pairs.\n",
            find_operations_cnt, union_operations_cnt, find_operations_cnt + union_operations_cnt, pairs_cnt);
    printf("A apresentação dos conjuntos precisaram de %lu operações elementares para %d nós.\n", complexity_cnt, N);
    printf("Nodes: %d\nPairs: %d\nLinks: %d\n", N, pairs_cnt, links_cnt);
    return;
}


/******************************************************************************
 * quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Quick Union algorithm
 *****************************************************************************/

void quick_union(int *id, int N, FILE * fp, int quietOut)
{

    int i, j, p, q;

    int pairs_cnt = 0;            /* connection pairs counter */
    int links_cnt = 0;            /* number of links counter */

    ulong find_operations_cnt = 0;
    ulong union_operations_cnt = 0;

    /* initialize; all disconnected */
    for (i = 0; i < N; i++) {
        id[i] = i;
    }

    /* read while there is data */
    while (fscanf(fp, "%d %d", &p, &q) == 2) {
        pairs_cnt++;
        i = p;
        j = q;

        /* do search first */
        find_operations_cnt++;
        while (i != id[i]) {
            i = id[i];
            find_operations_cnt += 2;
        }
        find_operations_cnt++;
        while (j != id[j]) {
            j = id[j];
            find_operations_cnt += 2;
        }
        if (i == j) {
            /* already in the same set; discard */
#if DEBUG
            printf("\t%d %d\n", p, q);
#endif
            continue;
        }

        /* pair has new info; must perform union */
        id[i] = j;

        union_operations_cnt++;
        links_cnt++;

        if (!quietOut)
            printf(" %d %d\n", p, q);
    }
    printf("QU: The number of links performed is %d for %d input pairs.\n",
            links_cnt, pairs_cnt);
    printf("QU: The number of elementary operations is %lu when searching, %lu when perfoming union, with a total of %lu operations for %d input pairs.\n",
            find_operations_cnt, union_operations_cnt, find_operations_cnt + union_operations_cnt, pairs_cnt);
    printf("Nodes: %d\nPairs: %d\nLinks: %d\n", N, pairs_cnt, links_cnt);
}


/******************************************************************************
 * weighted_quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Weighted Quick Union algorithm
 *****************************************************************************/

void weighted_quick_union(int *id, int N, FILE * fp, int quietOut)
{

    int i, j, p, q;
    int *sz = (int *) malloc(N * sizeof(int));

    int pairs_cnt = 0;            /* connection pairs counter */
    int links_cnt = 0;            /* number of links counter */

    ulong find_operations_cnt = 0;
    ulong union_operations_cnt = 0;

    /* initialize; all disconnected */
    for (i = 0; i < N; i++) {
        id[i] = i;
        sz[i] = 1;
    }

    /* read while there is data */
    while (fscanf(fp, "%d %d", &p, &q) == 2) {
        pairs_cnt++;
        /* do search first */
        for (i = p; i != id[i]; i = id[i], union_operations_cnt += 2);
        for (j = q; j != id[j]; j = id[j], union_operations_cnt += 2);

        if (i == j) {
            /* already in the same set; discard */
#if DEBUG
            printf("\t%d %d\n", p, q);
#endif
            continue;
        }

        /* pair has new info; must perform union; pick right direction */
        if (sz[i] < sz[j]) {
            id[i] = j;
            sz[j] += sz[i];
        }
        else {
            id[j] = i;
            sz[i] += sz[j];
        }
        union_operations_cnt += 6;
        links_cnt++;

        if (!quietOut)
            printf(" %d %d\n", p, q);
    }

    printf("WQU: The number of links performed is %d for %d input pairs.\n",
            links_cnt, pairs_cnt);
    printf("WQU: The number of elementary operation is %lu when serching, %lu when performing union, with a total of %lu operations for %d input pairs.\n",
            find_operations_cnt, union_operations_cnt, find_operations_cnt + union_operations_cnt, pairs_cnt);
    printf("Nodes: %d\nPairs: %d\nLinks: %d\n", N, pairs_cnt, links_cnt);
    free(sz);
    return;
}


/******************************************************************************
 * compressed_weighted_quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Compressed Weighted Quick Union algorithm
 *****************************************************************************/

void compressed_weighted_quick_union(int *id, int N, FILE * fp, int quietOut)
{
    int i, j, p, q, t, x;
    int *sz = (int *) malloc(N * sizeof(int));

    int pairs_cnt = 0;            /* connection pairs counter */
    int links_cnt = 0;            /* number of links counter */

    ulong find_operations_cnt = 0;
    ulong union_operations_cnt = 0;

    /* initialize; all disconnected */
    for (i = 0; i < N; i++) {
        id[i] = i;
        sz[i] = 1;
    }

    /* read while there is data */
    while (fscanf(fp, "%d %d", &p, &q) == 2) {
        pairs_cnt++;

        /* do search first */
        for (i = p; i != id[i]; i = id[i], find_operations_cnt += 2);
        for (j = q; j != id[j]; j = id[j], find_operations_cnt += 2);

        if (i == j) {
            /* already in the same set; discard */
#if DEBUG
            printf("\t%d %d\n", p, q);
#endif
            continue;
        }

        /* pair has new info; must perform union; pick right direction */
        if (sz[i] < sz[j]) {
            id[i] = j;
            sz[j] += sz[i];
            t = j;
        }
        else {
            id[j] = i;
            sz[i] += sz[j];
            t = i;
        }
        union_operations_cnt += 6;
        links_cnt++;

        /* retrace the path and compress to the top */
        for (i = p; i != id[i]; i = x, union_operations_cnt += 3) {
            x = id[i];
            id[i] = t;
        }
        for (j = q; j != id[j]; j = x, union_operations_cnt += 3) {
            x = id[j];
            id[j] = t;
        }
        if (!quietOut)
            printf(" %d %d\n", p, q);
    }
    printf("CWQU: The number of links performed is %d for %d input pairs.\n",
            links_cnt, pairs_cnt);
    printf("CWQU: The number of elementary operation is %lu when searching, %lu when performing union, with a total of %lu operations for %d input pairs.\n",
            find_operations_cnt, union_operations_cnt, find_operations_cnt + union_operations_cnt, pairs_cnt);
    printf("Nodes: %d\nPairs: %d\nLinks: %d\n", N, pairs_cnt, links_cnt);

    free(sz);
    return;
}

/******************************************************************************
 * (c) 2010-2019 AED Team
 * Last modified: abl 2019-03-01
 *
 * NAME
 *   palTab.c
 *
 * DESCRIPTION
 *   Main program for unique word finding with tables
 *
 * COMMENTS
 *   Code variant for distribution
 ******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <strings.h>
#define MAX_STR 100

typedef struct _st_texto {
    int  n_total_palavras;      /* total number of words */
    int  n_dist_palavras;       /* number of distinct words*/
    char **palavras;            /* Table of strings for words */
    int  *ocorrencias;          /* Table of integers counting occurrence */
} st_texto;

int NovaPalavra ( char *palavra, st_texto *t );


/******************************************************************************
 * LePalavra()
 *
 * Arguments: f - pointer to file where word will be read
 * Returns:  pointer to word just read
 * Side-Effects: none
 *
 * Description:
 *   Return pointer to local buffer with word, or NULL if file read failed
 *   Maximum word size MAX_STR
 *****************************************************************************/

char *LePalavra ( FILE *f )
{
    static char palavra[MAX_STR];       /* note static local buffer returned */

    if ( fscanf ( f, "%s", palavra ) ==1 )
        return (palavra);
    else
        return ((char *) NULL);
}


/******************************************************************************
 * AbreFicheiro()
 *
 * Arguments: nome - pointer to string holding name of file to open
 *            mode - pointer to string with 'r'/'w' etc mode for file open
 * Returns: pointer to opened file
 * Side-Effects: exits if given file cannot be opened with given mode
 *
 * Description:
 *   Open named file in requested mode, message stderr and exit if open fails
 *****************************************************************************/

FILE *AbreFicheiro ( char *nome, char *mode )
{
    FILE *fp;
    fp = fopen ( nome, mode );
    if ( fp == NULL ) {
        fprintf ( stderr, "ERROR: cannot open file '%s'\n", nome);
        exit ( 1 );                                 /* non-zero exit status */
    }
    return (fp);
}

ushort isNew(FILE *file, char *word){
    long lastPosition = SEEK_CUR;
    char *search = NULL;
    ushort isNew = 1;

    rewind(file);
    while ((search = LePalavra(file)) != NULL && SEEK_CUR < lastPosition) {
        if (strcasecmp(word, search) == 0) {
            isNew = 0;
            break;
        }
    }
    fseek(file, 0, lastPosition);
    return isNew;
}


/******************************************************************************
 * AlocaTabelaPalavras()
 *
 * Arguments: ficheiro - pointer to string holding name of file to open
 *            st_texto - pointer to structure where information will be saved
 * Returns: (none)
 * Side-Effects: none
 *
 * Description:
 *   Read input file to find dimensions, allocate and initialize tables
 *****************************************************************************/

void AlocaTabelaPalavras ( char *ficheiro, st_texto *t)
{
    FILE *fp;
    char *palavra;
    int i;

    (*t).n_total_palavras = 0;
    (*t).n_dist_palavras = 0;
    t->palavras = NULL;
    t->ocorrencias = NULL;
    fp = AbreFicheiro ( ficheiro, "r" );
    while ( ( palavra = LePalavra ( fp ) ) != NULL ) {
        if (isNew(fp, palavra)) t->n_dist_palavras++;
        t->n_total_palavras++;
    }

    fclose ( fp );
    printf ( "Words count: %d\n", (*t).n_total_palavras );

    (*t).palavras = (char **) malloc(t->n_dist_palavras * sizeof(char *));
    if ( (*t).palavras == NULL ) {
        fprintf ( stderr, "ERROR: not enough memory available!\n" );
        exit ( 2 );
    }
    (*t).ocorrencias = (int *) malloc(t->n_dist_palavras * sizeof(int));
    if ( (*t).ocorrencias == NULL ) {
        fprintf ( stderr, "ERROR: not enough memory available!\n" );
        exit ( 4 );
    }
    


    return;

}


/******************************************************************************
 * NovaPalavra()
 *
 * Arguments: palavra - pointer to string holding a word
 *            st_texto - pointer to structure where run information is kept
 * Returns:  int index of word in table
 * Side-Effects: none
 *
 * Description:
 *   Search for a word in the table. If the word is not found returns -1,
 *   Otherwise returns the position of the word in the table
 *****************************************************************************/

int NovaPalavra ( char *palavra, st_texto *t )
{
    int i = 0;
    while ( i < (*t).n_dist_palavras ) {
        if ( strcmp ( (*t).palavras[i], palavra ) == 0 )
            return (i);
        i++;
    }
    return (-1);
}


/******************************************************************************
 * PreencheTabelaPalavras()
 *
 * Arguments: ficheiro - pointer to string holding name of file to open
 *            st_texto - pointer to structure where information will be saved
 * Returns: (none)
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/

void PreencheTabelaPalavras ( char *ficheiro, st_texto *t )
{
    FILE *f;
    int n, i = 0 , len;
    char *palavra;

    f = AbreFicheiro ( ficheiro, "r" );
    while ( ( palavra = LePalavra ( f ) ) != NULL ) {
        if ( ( n = NovaPalavra ( palavra, &(*t) ) ) == -1 ) {
            t->palavras[i] = (char *) malloc((strlen(palavra) + 1) * sizeof(char));
            strcpy ( (*t).palavras[i], palavra );
            (*t).ocorrencias[i]++;
            i++;
        }
        else {
            (*t).ocorrencias[n]++;
        }
    }
    fclose ( f );
    return;
}


/******************************************************************************
 * EscreveFicheiro()
 *
 * Arguments: ficheiro - pointer to string holding name of file to save
 *            st_texto - pointer to structure where information is kept
 * Returns: (none)
 * Side-Effects: none
 *
 * Description:
 *   Open output file, write table of words.
 *****************************************************************************/

void EscreveFicheiro ( char *ficheiro, st_texto *t )
{
    FILE *f;
    char *nome;
    int i = 0;
    nome = (char *) malloc((strlen(ficheiro) + strlen(".palavras\0") + 1) * sizeof(char));
    /* including dot (.) extension and string termination, see below */
    if ( nome == NULL ) {
        fprintf ( stderr, "ERROR: not enough memory available!\n" );
        exit ( 5 );
    }
    strcpy ( nome, ficheiro );
    strcat ( nome, ".palavras" );
    f = AbreFicheiro ( nome, "w" );
    for ( i = 0; i < (*t).n_dist_palavras; i++ ) {
        fprintf ( f, "%d: %s\n", (*t).ocorrencias[i], (*t).palavras[i] );
    }
    printf ( "Count of distinct words: %d\n", (*t).n_dist_palavras );
    fclose ( f );

    /* Anything else I should do here? */
    free(nome);
    for (i = 0; i < t->n_dist_palavras; i++) {
        free(t->palavras[i]);
    }
    free(t->palavras);
    free(t->ocorrencias);

    return;
}


/******************************************************************************
 * main()
 *
 * Arguments: argc - counter of number of arguments in call
 *            argv - pointer to array of strings holding the arguments
 * Returns: exit status
 * Side-Effects: none
 *
 * Description:
 *   Get filename, read input file and make word table, write output file
 *****************************************************************************/

int main ( int argc, char **argv )
{
    int i;
    st_texto st_palavras;

    if ( argc < 2 ) {
        fprintf ( stderr, "ERROR: missing filename in argument!\n" );
        exit ( 6 );
    }
    AlocaTabelaPalavras ( argv[1], &st_palavras );
    //PreencheTabelaPalavras ( argv[1],&st_palavras );
    EscreveFicheiro ( argv[1], &st_palavras );

    return (0);
}

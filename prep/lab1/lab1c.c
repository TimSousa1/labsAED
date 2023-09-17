#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FREQ_SIZE 20


typedef struct _histogram
{
   unsigned int* frequency;
   unsigned int numberLetters;
} Histogram;

Histogram* initHistogram(int numberLetters)
{
   Histogram* histograma;
   if((histograma = (Histogram*)malloc(sizeof(Histogram))) == NULL)  {
      exit(2);
   }

   histograma->numberLetters = numberLetters;
   if((histograma->frequency =
       (unsigned int*)malloc(sizeof(unsigned int)*FREQ_SIZE)) == NULL)  {
      exit(3);
   }

   for(unsigned int i = 0; i < FREQ_SIZE; i++)
      histograma->frequency[i] = 0;

   return histograma;
}


int main(int argc, char** argv)
{
    if(argc != 2) {
       printf("O programa foi invocado incorretamente.\n");
       printf("Deve ser invocado com \'%s \"texto\"\'\n", argv[0]);
       exit(1);
    }

    Histogram* histograma = initHistogram(strlen(argv[1]));
    for(unsigned int i = 0; i < histograma->numberLetters; i++)  {
       int converted = toupper(argv[1][i]) - 'A';

       if(converted < 0 || converted > ('Z'-'A')) continue;
       histograma->frequency[converted] += 1;
    }

    for(unsigned int i = 0; i < FREQ_SIZE; i++) {
       printf("%c : %d\n", 'A' + i, histograma->frequency[i]);
    }

    free(histograma->frequency);
    free(histograma);

    return 0;
}

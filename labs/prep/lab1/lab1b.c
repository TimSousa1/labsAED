#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FREQ_SIZE 26

typedef struct _histogram
{
   unsigned int numberLetters;
   unsigned int frequency[FREQ_SIZE];
} histogram;

int main(int argc, char** argv)
{
   if(argc != 2)  {
      printf("O programa foi invocado incorretamente.\n");
      printf("Deve ser invocado com \'%s \"texto\"\'\n", argv[0]);
      exit(1);
   }

   histogram histograma;
   histograma.numberLetters = strlen(argv[1]);

  for (int i = 0; i < FREQ_SIZE; i++) histograma.frequency[i] = 0;

   for(unsigned int i = 0; i < histograma.numberLetters; i++)  {
      int converted = toupper(argv[1][i]) - 'A';

      histograma.frequency[converted] += 1;
   }

   for(unsigned int i = 0; i < FREQ_SIZE; i++)  {
      printf("%c : %d\n", 'A' + i, histograma.frequency[i]);
   }
   return 0;
}

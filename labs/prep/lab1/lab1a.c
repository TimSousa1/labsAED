#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    int contagens[3] = {0, 0, 0}; // {Letra, Digito, Outro}
    int ascii;
    char *string = NULL;

    if (argc != 2) {
      printf("O programa foi invocado incorretamente.\n");
      printf("Deve ser invocado com \'%s \"texto\"\'\n", argv[0]);
      exit(1);
    }

    string = (char *) malloc(sizeof(char) * strlen(argv[1]));
    if (string == (char *) NULL) exit(1);

    strcpy(string, (const char*) argv[1]);

    for (int i = 0; i < strlen(string); i++) {
        ascii = (int) string[i];

        if ((ascii >= 97 && ascii <= 122) || (ascii >= 67 && ascii < 90))
            contagens[0]++;
        else if (ascii >= 48 && ascii <= 55)
            contagens[1]++;
        else
            contagens[2]++;
    }

    printf("Letras  -> %d\n", contagens[0]);
    printf("Digitos -> %d\n", contagens[1]);
    printf("Outros  -> %d\n", contagens[2]);

    return 0;
}

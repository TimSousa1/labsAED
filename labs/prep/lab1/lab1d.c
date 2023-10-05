#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/* FILENAME: lab1d.c
 * DESCRIPTION: receives an array of integers and stores them in a linked
 * list; then a sweep through the list is made and every odd number is
 * removed from it
 */



typedef struct _list {
   int number;
   struct _list *next;
} list;

list *head;
list *tail;



/* FUNCTION: init_list
 * ARGUMENTS: none
 * DESCRIPTION: initializes the list of numbers by setting the head and tail
 * pointers to null (head is a pointer to the beggining of the list and tail
 * to the end of the list)
 * RETURN VALUE: none
 */
void init_list(void)
{
   head = NULL;
   tail = NULL;

   return;
}



/* FUNCTION: new_num
 * ARGUMENTS: int num --> new number that wants to be added to the list
 * DESCRIPTION: allocates memory for a new struct in which the new number
 * will be stored; the structs are the nodes of the list
 * RETURN VALUE: pointer to the struct dinamically allocated
 */
list *new_num(int num)
{
   list *new = NULL;

   new = (list *) malloc(sizeof(list));
   if(new == NULL) exit(EXIT_FAILURE);

   new->number = num;
   new->next = NULL;

   return new;
}



/* FUNCTION: insert_element
 * ARGUMENTS: list *node --> a list element that has been allocated and
 * contains a number that wants to be added to the list
 * DESCRIPTION: inserts the struct at the end of the list and updates the
 * list's pointers, head and tail
 * RETURN VALUE: none
 */
void insert_element(list *node)
{
   if(head == NULL) head = node;
   else if(head->next == NULL) head->next = node;
   else tail->next = node;

   tail = node;

   return;
}



/* FUNCTION: create_list
 * ARGUMENTS: char **numbers --> argv from main, which contains the numbers
 * that will be inserted in the list DESCRIPTION: reads every number typed by
 * the user and creates nodes which are later inserted in the list
 * RETURN VALUE: none
 */
void create_list(char **numbers)
{
   int integer = 0, i = 1;
   char *error = NULL;
   list *element = NULL;

   while(numbers[i] != NULL) {
      integer = strtol(numbers[i++], &error, 10);
      if(*error != '\0') exit(EXIT_FAILURE);

      element = new_num(integer);
      insert_element(element);
   }

   return;
}



/* FUNCTION: print_list
 * ARGUMENTS: none
 * DESCRIPTION: goes through the linked list and prints every number
 * RETURN VALUE: none
 */
void print_list(void)
{
   list *aux = head;

   printf("[ ");
   while(aux != NULL) {
      printf("%d ", aux->number);
      aux = aux->next;
   }
   printf("]\n");

   return;
}



/* FUNCTION: remove_next
 * ARGUMENTS: list *previous_node --> a pointer to the node
 * right before the one who is going to get removed from the
 * list
 * DESCRIPTION: removes and frees the memory of the node right
 * after the node pointed by previous_node
 * RETURN VALUE: none
 */
void remove_next(list *previous_node)
{
  list *removed;
  removed = previous_node->next;
   previous_node->next = previous_node->next->next;
  free(removed);
   return;
}



/* FUNCTION: remove_odd_numbers
 * ARGUMENTS: none
 * DESCRIPTION: does a sweep through the linked list
 * and checks every number, if its a odd number then it
 * removes the number from the list and frees the
 * memmory of that node
 * RETURN VALUE: none
 */
void remove_odd_numbers(void)
{
   list *current = head, *previous = NULL;

   while(current != NULL) {
      if(current->number % 2 != 0) {
         if (!previous) {
          head = head->next;
          free(current);
      } else remove_next(previous);

         /* if the removed node was the head of the list */
         if(previous == NULL) current = head;
         else {
            current = previous->next;
         }
      } else {
         previous = current;
         current = current->next;
      }
   }

   return;
}



/* FUNCTION: free_list
 * ARGUMENTS: none
 * DESCRIPTION: does a sweep through the list and frees all memmory allocated
 * RETURN VALUE: none
 */
void free_list(void)
{
   list *aux = NULL;

   while(head != NULL) {
      aux = head;
      head = head->next;
      free(aux);
   }

   return;
}


/* main */
int main(int argc, char **argv)
{
   if(argc < 2) {
      printf("O programa foi invocado incorretamente.\n");
      printf("Deve ser invocado com \'%s [inteiro 1] [inteiro 2] ...\'\n",
             argv[0]);
      exit(EXIT_FAILURE);
   }

   init_list();
   create_list(argv);

   print_list();
   printf("Não gosto nada de número ímpares... Deixa-me cá correr os números para ver se eles andam por aí...\n\n\n");

   remove_odd_numbers();

   print_list();
   printf("Ah... Bem melhor!\n");

   free_list();

   return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include "linkedList.h"


int main(int argc, char const *argv[])
{
    linked_list_t list;
    initialize_list(&list);
    int *a = (int *)malloc(sizeof(int));
    *a = 1;
    int *b = (int *)malloc(sizeof(int));
    *b = 2;
    int *c = (int *)malloc(sizeof(int));
    *c = 3;
    int *d = (int *)malloc(sizeof(int));
    *d = 4;

    add_node(&list, a);
    add_node(&list, b);
    add_node(&list, c);
    printf("elemento in posizione 0:%d\n", *(int *)get_nth_element(&list, 0));
    printf("elemento in posizione 1:%d\n", *(int *)get_nth_element(&list, 1));
    printf("elemento in posizione 2:%d\n", *(int *)get_nth_element(&list, 2));
    printf("size:%d\n", list.size);
    remove_node(&list, d);
    remove_node(&list, b);
    printf("elemento rimosso\n");
    printf("elemento in posizione 0:%d\n", *(int *)get_nth_element(&list, 0));
    printf("elemento in posizione 1:%d\n", *(int *)get_nth_element(&list, 1));
    printf("size:%d\n", list.size);

    free_list(&list);
    free(d);

    return 0;
}

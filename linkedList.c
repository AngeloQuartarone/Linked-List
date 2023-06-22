#include <pthread.h>
#include <stdlib.h>

typedef struct node
{
    void *data;
    struct node *next;
} node_t;

typedef struct linked_list
{
    node_t *head;
    pthread_mutex_t lock;
    int size;
} linked_list_t;

void initialize_list(linked_list_t *list)
{
    list->head = NULL;
    pthread_mutex_init(&list->lock, NULL);
    list->size = 0;
}

void add_node(linked_list_t *list, void *data)
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = data;
    pthread_mutex_lock(&list->lock);
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
    pthread_mutex_unlock(&list->lock);
}

void remove_node(linked_list_t *list, void *data)
{
    pthread_mutex_lock(&list->lock);
    node_t *current = list->head;
    node_t *previous = NULL;
    while (current != NULL)
    {
        if (current->data == data)
        {
            if (previous == NULL)
            {
                list->head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            free(current);
            break;
        }
        previous = current;
        current = current->next;
    }
    pthread_mutex_unlock(&list->lock);
}

void *get_nth_element(linked_list_t *list, int n)
{
    if (n < 0 || n >= list->size)
    {
        return NULL;
    }
    pthread_mutex_lock(&list->lock);
    node_t *current = list->head;
    for (int i = 0; i < n; i++)
    {
        current = current->next;
    }
    void *data = current->data;
    pthread_mutex_unlock(&list->lock);
    return data;
}

void free_list(linked_list_t *list)
{
    pthread_mutex_lock(&list->lock);
    node_t *current = list->head;
    while (current != NULL)
    {
        node_t *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    list->head = NULL;
    list->size = 0;
    pthread_mutex_unlock(&list->lock);
}
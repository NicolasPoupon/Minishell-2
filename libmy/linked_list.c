/*
** EPITECH PROJECT, 2021
** linked_list.c
** File description:
** fct linked list
*/

#include <stdlib.h>
#include "../include/my.h"
#include "../include/p.h"

struct linked_list *delete_list(struct linked_list *list,
struct linked_list *delete)
{
    struct linked_list *list_cpy = list;
    struct linked_list *buff;
    int i = 0;

    if (list == delete) {
        list_cpy = list->next;
        free(list);
        return list_cpy;
    }
    while (list_cpy->next != delete) {
        list_cpy = list_cpy->next;
        i++;
    }
    buff = list_cpy->next;
    list_cpy->next = list_cpy->next->next;
    free(buff);
    return list;
}

struct linked_list *add_list(struct linked_list *list, struct linked_list *new,
int nb)
{
    struct linked_list *list_cpy = list;

    if (nb == 0) {
        new->next = list;
        return new;
    }
    for (int i = 0; i < nb - 1 && list_cpy->next != NULL; i++)
        list_cpy = list_cpy->next;
    new->next = list_cpy->next;
    list_cpy->next = new;
    return list;
}

void free_linked_list(struct linked_list *list)
{
    struct linked_list *next;

    while (list != NULL) {
        next = list->next;
        free(list);
        list = next;
    }
    free(list);
}

struct linked_list *create_new_list(void)
{
    struct linked_list *new;

    return new;
}

struct linked_list *create_linked_list(int size)
{
    struct linked_list *new = NULL;
    struct linked_list *last = NULL;

    for (int i = 0; i != size; i++) {
        if (i != 0)
            new = create_new_list();
        new = malloc(sizeof(struct linked_list) * 1);
        if (new == NULL)
            return put_error_null("malloc error new linked list\n");
        new->next = last;
        last = new;
    }
    return new;
}

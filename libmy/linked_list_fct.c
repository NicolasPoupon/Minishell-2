/*
** EPITECH PROJECT, 2021
** linked_list.c
** File description:
** fct linked list
*/

#include <stdlib.h>
#include "../include/my.h"
#include "../include/p.h"

int len_linked_list(struct linked_list *list)
{
    struct linked_list *list_cpy = list;
    int size = 0;

    while (list_cpy != NULL) {
        size++;
        list_cpy = list_cpy->next;
    }
    return size;
}

struct linked_list *get_list(struct linked_list *list, char *name)
{
    while (list != NULL) {
        if (compare_str(list->name, name) == 0)
            return list;
        list = list->next;
    }
    return NULL;
}

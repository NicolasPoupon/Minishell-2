/*
** EPITECH PROJECT, 2021
** main_minishell.c
** File description:
** main minishell
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../include/my.h"
#include "../include/p.h"

int main(int ac, char **av, char **env)
{
    if (ac != 1) {
        write(2, "syntax error\n", 13);
        exit(84);
    }
    return (minishell(ac, av, env));
}

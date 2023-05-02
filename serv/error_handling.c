/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** error_handling
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool usage_display(int ac, char **av)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        printf("USAGE: ./myteams_server port\n\n");
        printf("\tport\tis the port number on which the ");
        printf("server socket listens.\n");
        return true;
    }
    return false;
}

bool error(int ac, char **av)
{
    return false;
}

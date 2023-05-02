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
        printf("USAGE: ./myteams_cli ip port\n");
        printf("\tip\tis the server ip adress on which ");
        printf("the server socket listens\n");
        printf("\tport\tis the port number on which the ");
        printf("server socket listens.\n");
        return true;
    }
    return false;
}

bool error(int ac, char **av)
{
    if (ac != 3) {
        printf("Error: Invalid number of arguments.\n");
        return true;
    }
    return false;
}

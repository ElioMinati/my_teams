/*
** EPITECH PROJECT, 2022
** teams
** File description:
** main
*/

#include <stdbool.h>
#include <stdlib.h>
#include "shared_error_handling.h"
#include "server.h"

int main(int ac, char **av)
{
    if (usage_display(ac, av))
        return 0;
    if (error(ac, av))
        return 84;
    start_server(atoi(av[1]));
    return 0;
}

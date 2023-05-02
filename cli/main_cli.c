/*
** EPITECH PROJECT, 2023
** teams
** File description:
** main
*/

#include <stdlib.h>
#include "client.h"
#include "shared_error_handling.h"

int main(int ac, char **av)
{
    if (usage_display(ac, av))
        return 0;
    if (error(ac, av))
        return 84;
    return launch_client(av[1], atoi(av[2]));
}

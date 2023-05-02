/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** write_utils
*/

#include <unistd.h>
#include <string.h>
#include "socket_utils.h"

void write_to_socket(int sock, char *buf)
{
    fd_set write_fds;

    FD_ZERO(&write_fds);
    FD_SET(sock, &write_fds);
    select(FD_SETSIZE, NULL, &write_fds, NULL, NULL);
    write(sock, buf, strlen(buf));
}

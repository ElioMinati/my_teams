/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** fd_utils
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "str_utils.h"
#include "server.h"

void reset_file_descriptors(server_t *server)
{
    FD_ZERO(&server->read_fds);
    FD_SET(server->socket, &server->read_fds);
    for (int i = 0; i < server->nb_clients_connected; i++) {
        FD_SET(server->clients_connected[i].socket, &server->read_fds);
    }
}

void reset_client_file_descriptors(client_t *client)
{
    FD_ZERO(&client->read_fds);
    FD_SET(client->socket, &client->read_fds);
    FD_SET(STDIN_FILENO, &client->read_fds);
}

char *read_string_from_fd(int fd)
{
    char *dest = malloc(2 * sizeof(char));
    char tmp_c;
    int tmp_len = 1;

    if (read(fd, &tmp_c, 1) < 1) {
        free(dest);
        return NULL;
    }
    dest[0] = tmp_c;
    dest[1] = '\0';
    while (read(fd, &tmp_c, 1) > 0) {
        tmp_len++;
        dest = str_realloc(dest);
        dest[tmp_len - 1] = tmp_c;
        dest[tmp_len] = '\0';
        if (strcmp(dest + (tmp_len - 2), CRLF) == 0)
            break;
    }
    dest[tmp_len - 2] = '\0';
    return dest;
}

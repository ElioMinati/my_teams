/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** select_parsing
*/

#include <unistd.h>
#include "client.h"

bool handle_server_select(int fd, client_t *client)
{
    if (FD_ISSET(fd, &client->read_fds) && fd == client->socket) {
        recieve_from_server(client);
        return 1;
    }
    if (FD_ISSET(fd, &client->read_fds) && fd == STDIN_FILENO) {
        parse_and_send_to_server(client);
        return 1;
    }
    return 0;
}

void handle_client_select(client_t *client)
{
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (handle_server_select(i, client))
            break;
    }
}

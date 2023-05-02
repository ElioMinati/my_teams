/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** select_parsing
*/

#include "server.h"
#include "client_utils.h"

bool handle_server_select(int fd, server_t *server)
{
    if (FD_ISSET(fd, &server->read_fds) && fd == server->socket) {
        accept_new_client(server);
        return 1;
    }
    if (FD_ISSET(fd, &server->read_fds) && is_client_connected(
        server->clients_connected, server->nb_clients_connected, fd)) {
        parse_command_for_client(server, fd);
        return 1;
    }
    return 0;
}

void handle_select(server_t *server)
{
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (handle_server_select(i, server))
            break;
    }
}

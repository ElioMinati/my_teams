/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** user_connection_utils
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "server.h"

bool is_client_connected(client_t *clients, int nb_clients, int client_socket)
{
    if (clients == NULL || nb_clients == 0)
        return false;
    for (int i = 0; i < nb_clients; i++) {
        if (clients[i].socket == client_socket)
            return true;
    }
    return false;
}

int is_client_connected_by_uuid(client_t *clients, int nb_clients, char *uuid)
{
    if (clients == NULL || nb_clients == 0)
        return false;
    for (int i = 0; i < nb_clients; i++) {
        if (clients[i].uuid != NULL && strcmp(clients[i].uuid, uuid) == 0)
            return 1;
    }
    return 0;
}

void disconnect_client(server_t *server, int client_socket, bool kill)
{
    int new_i = 0;

    for (int i = 0; i < server->nb_clients_connected; i++, new_i++) {
        if (server->clients_connected[i].socket == client_socket) {
            send_user_logged_out_event(server, client_socket);
            close(client_socket);
            new_i--;
            continue;
        }
        server->clients_connected[new_i] = server->clients_connected[i];
    }
    server->nb_clients_connected--;
    server->clients_connected = realloc(server->clients_connected,
        (server->nb_clients_connected + 1) * sizeof(struct client_s));
    FD_CLR(client_socket, &server->read_fds);
}

/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** client_utils
*/

#include <stdlib.h>
#include <unistd.h>
#include "server.h"
#include "str_utils.h"
#include "socket_utils.h"

client_t connect_new_client(int server_socket)
{
    client_t new_client;
    socklen_t lendest = sizeof(new_client.address);

    new_client.uuid = NULL;
    new_client.user_name = NULL;
    new_client.context.type = TEAM;
    new_client.context.channel_uuid = NULL;
    new_client.context.team_uuid = NULL;
    new_client.context.thread_uuid = NULL;
    new_client.socket = accept(server_socket,
        (struct sockaddr *)&new_client.address, &lendest);
    write_to_socket(new_client.socket, str_concat(
        "201 Service ready for new user.", CRLF));
    return new_client;
}

void accept_new_client(server_t *server)
{
    if (server->nb_clients_connected == 0) {
        server->clients_connected = malloc(1 * sizeof(struct client_s));
    } else {
        server->clients_connected = realloc(server->clients_connected,
            (server->nb_clients_connected + 2) * sizeof(struct client_s));
    }
    server->clients_connected[server->nb_clients_connected] =
        connect_new_client(server->socket);
    FD_SET(server->clients_connected[server->nb_clients_connected].socket,
        &server->read_fds);
    server->nb_clients_connected++;
}

client_t *get_client(server_t *server, int client_socket)
{
    for (int i = 0; i < server->nb_clients_connected; i++) {
        if (server->clients_connected[i].socket == client_socket)
            return &server->clients_connected[i];
    }
    return NULL;
}

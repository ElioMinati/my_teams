/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** init_server
*/

#include <stdlib.h>
#include <time.h>
#include "socket_utils.h"
#include "server.h"

void init_server(server_t *server, int port)
{
    struct sockaddr_in server_a = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr = INADDR_ANY
    };

    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    server->address = server_a;
    bind(server->socket, (struct sockaddr *)&server->address,
        sizeof(server->address));
    listen(server->socket, MAX_CLIENTS);
    FD_ZERO(&server->read_fds);
    FD_SET(server->socket, &server->read_fds);
    server->clients_connected = NULL;
    server->nb_clients_connected = 0;
    server->database = load_database();
}

static void destroy_server(server_t *server)
{
    free(server->clients_connected);
}

void start_server(int port)
{
    server_t server;
    time_t t;

    srand((unsigned int)time(&t));
    init_server(&server, port);
    while (1) {
        select(FD_SETSIZE, &server.read_fds, NULL, NULL, NULL);
        handle_select(&server);
        reset_file_descriptors(&server);
    }
    destroy_server(&server);
}

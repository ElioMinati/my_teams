/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** init_client
*/

#include <arpa/inet.h>
#include <sys/select.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server.h"
#include "str_utils.h"
#include "socket_utils.h"

static void init_client_vars(client_t *client)
{
    client->user_name = NULL;
    client->uuid = NULL;
    client->disconnect = false;
}

bool connect_client(client_t *client, const char *ip, int port)
{
    FD_ZERO(&client->read_fds);
    struct sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr = inet_addr(ip)
    };

    client->socket = socket(AF_INET, SOCK_STREAM, 0);
    client->address = address;
    init_client_vars(client);
    if (connect(client->socket, (struct sockaddr *)&client->address,
        sizeof(client->address)) < 0) {
        printf("Unable to connect to: %s with port: %i.\n", ip, port);
        return false;
    }
    FD_SET(client->socket, &client->read_fds);
    FD_SET(STDIN_FILENO, &client->read_fds);
    return true;
}

int launch_client(const char *ip, int port)
{
    client_t client;

    if (!connect_client(&client, ip, port))
        return 84;
    while (!client.disconnect) {
        select(FD_SETSIZE, &client.read_fds, NULL, NULL, NULL);
        handle_client_select(&client);
        reset_client_file_descriptors(&client);
    }
    return 0;
}

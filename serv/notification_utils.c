/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** notification_utils
*/

#include "server.h"
#include "socket_utils.h"

void send_notification_to_all(server_t *server, char *msg)
{
    for (int i = 0; i < server->nb_clients_connected; i++) {
        if (server->clients_connected[i].uuid == NULL)
            continue;
        write_to_socket(server->clients_connected[i].socket, msg);
    }
}

void send_notification_to_all_except(server_t *server, char *msg,
    int ex_socket)
{
    for (int i = 0; i < server->nb_clients_connected; i++) {
        if (server->clients_connected[i].uuid == NULL ||
            server->clients_connected[i].socket == ex_socket)
            continue;
        write_to_socket(server->clients_connected[i].socket, msg);
    }
}

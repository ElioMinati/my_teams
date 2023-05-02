/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** user_logout
*/

#include <string.h>
#include <unistd.h>
#include "str_utils.h"
#include "server.h"
#include "client_utils.h"
#include "protocol.h"
#include "logging_server.h"
#include "socket_utils.h"

void logout_user(int client_socket, server_t *server, char *cmd)
{
    client_t *requested_client = get_client(server, client_socket);

    server_event_user_logged_out(requested_client->uuid);
    write_to_socket(client_socket, str_concat(MSG_299, CRLF));
    send_user_logged_out_event(server, client_socket);
    requested_client->user_name = NULL;
    requested_client->uuid = NULL;
}

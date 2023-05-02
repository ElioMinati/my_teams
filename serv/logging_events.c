/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** logging_events
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "client_utils.h"
#include "str_utils.h"

void send_user_logged_in_event(server_t *server, int client_socket)
{
    client_t *client = get_client(server, client_socket);
    char *login_msg = malloc((strlen(client->uuid) + strlen(client->user_name)
        + 45) * sizeof(char));

    sprintf(login_msg, "211 User \"%s\" with name \"%s\" logged in.",
        client->uuid, client->user_name);

    send_notification_to_all_except(server, str_concat(login_msg, CRLF),
        client_socket);
}

void send_user_logged_out_event(server_t *server, int client_socket)
{
    client_t *client = get_client(server, client_socket);
    char *login_msg = NULL;

    if (client->uuid == NULL)
        return;
    login_msg = malloc((strlen(client->uuid) + strlen(client->user_name)
        + 45) * sizeof(char));
    sprintf(login_msg, "212 User \"%s\" with name \"%s\" logged out.",
        client->uuid, client->user_name);

    send_notification_to_all_except(server, str_concat(login_msg, CRLF),
        client_socket);
}

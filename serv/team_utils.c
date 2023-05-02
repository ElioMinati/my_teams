/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** team_utils
*/

#include <string.h>
#include <unistd.h>
#include "server.h"
#include "str_utils.h"
#include "client_utils.h"
#include "socket_utils.h"

bool team_with_same_name_exists(team_t **teams, char *name)
{
    for (int i = 0; teams[i] != NULL; i++) {
        if (strcmp(teams[i]->name, name) == 0)
        return true;
    }
    return false;
}

team_t *get_team(server_t *server, char *uuid)
{
    if (uuid == NULL)
        return NULL;
    for (int i = 0; server->database.teams[i] != NULL; i++) {
        if (strcmp(server->database.teams[i]->uuid, uuid) == 0)
            return server->database.teams[i];
    }
    return NULL;
}

void send_notification_to_team(server_t *server, team_t *team,
    char *msg_to_send, char *uuid_exempt)
{
    client_t *tmp_client = NULL;

    for (int i = 0; team->subscribed_users_uuid[i] != NULL; i++) {
        if (uuid_exempt != NULL && strcmp(uuid_exempt,
            team->subscribed_users_uuid[i]) == 0)
            continue;
        if (is_client_connected_by_uuid(server->clients_connected,
            server->nb_clients_connected, team->subscribed_users_uuid[i])) {
            tmp_client = get_client_by_uuid(server,
                team->subscribed_users_uuid[i]);
            write_to_socket(tmp_client->socket, str_concat(msg_to_send, CRLF));
        }
    }
}

bool is_user_subscribed_to_team(team_t *team, char *client_uuid)
{
    for (int i = 0; team->subscribed_users_uuid[i] != NULL; i++) {
        if (strcmp(team->subscribed_users_uuid[i], client_uuid) == 0)
            return true;
    }
    return false;
}

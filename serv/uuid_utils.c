/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** uuid_utils
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"

char *generate_new_uuid(int type)
{
    char *uuid = malloc((UUID_LEN + 1) * sizeof(char));

    for (int i = 0; i < UUID_LEN; i++) {
        uuid[i] = UUID_CHARS[rand() % strlen(UUID_CHARS)];
    }
    uuid[UUID_LEN] = '\0';
    uuid[(int)(UUID_LEN / 4) + type] = '-';
    uuid[(int)(UUID_LEN / 3) + type] = '-';
    uuid[(int)(UUID_LEN / 2) + type] = '-';
    return uuid;
}

bool does_team_uuid_exist(server_t *server, char *uuid)
{
    for (int i = 0; server->database.teams[i] != NULL; i++) {
        if (strcmp(server->database.teams[i]->uuid, uuid) == 0)
            return true;
    }
    return false;
}

bool does_channel_uuid_exist(server_t *server, char *team_uuid, char *uuid)
{
    team_t *team = get_team(server, team_uuid);

    if (team == NULL)
        return false;
    for (int i = 0; team->channels[i] != NULL; i++) {
        if (strcmp(team->channels[i]->uuid, uuid) == 0)
            return true;
    }
    return false;
}

bool does_thread_uuid_exist(server_t *server, char *team_uuid,
    char *channel_uuid, char *uuid)
{
    team_t *team = get_team(server, team_uuid);
    channel_t *channel = get_channel_from_team(team, channel_uuid);
    if (team == NULL || channel == NULL || uuid == NULL)
        return false;
    for (int i = 0; channel->threads[i] != NULL; i++) {
        if (strcmp(channel->threads[i]->uuid, uuid) == 0)
            return true;
    }
    return false;
}

bool is_user_uuid_alread_logged_in(server_t *server, char *uuid)
{
    if (uuid == NULL)
        return false;
    for (int i = 0; i < server->nb_clients_connected; i++) {
        if (server->clients_connected[i].uuid != NULL &&
            strcmp(server->clients_connected[i].uuid, uuid) == 0)
            return true;
    }
    return false;
}

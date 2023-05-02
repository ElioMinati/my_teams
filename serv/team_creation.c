/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** team_creation
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"
#include "protocol.h"
#include "logging_server.h"
#include "str_utils.h"
#include "socket_utils.h"

int get_teams_length(team_t **teams)
{
    int i = 0;

    for (; teams[i] != NULL; i++);
    return i;
}

team_t **add_new_team(team_t **current, char *name, char *desc, char *creator)
{
    int current_len = get_teams_length(current);
    current = realloc(current, (current_len + 2) * sizeof(struct team_s *));
    current[current_len] = malloc(sizeof(struct team_s));
    current[current_len]->channels = malloc(sizeof(struct channel_s));
    current[current_len]->channels[0] = NULL;
    current[current_len]->creator_uuid = malloc((strlen(creator) + 1) *
        sizeof(char));
    current[current_len]->creator_uuid =
        strcpy(current[current_len]->creator_uuid, creator);
    current[current_len]->name = malloc((strlen(name) + 1) * sizeof(char));
    current[current_len]->name = strcpy(current[current_len]->name, name);
    current[current_len]->description = malloc((strlen(desc) + 1) *
        sizeof(char));
    current[current_len]->description =
        strcpy(current[current_len]->description, desc);
    current[current_len]->uuid = generate_new_uuid(1);
    current[current_len]->subscribed_users_uuid = malloc(1 * sizeof(char *));
    current[current_len]->subscribed_users_uuid[0] = NULL;
    current[current_len + 1] = NULL;
    return current;
}

void send_create_team_events(server_t *server, client_t *client,
    team_t *new_team)
{
    char *reply = malloc((strlen(new_team->name) + 100 +
        strlen(new_team->description) + strlen(new_team->uuid)) *sizeof(char));
    char *evt_reply = malloc((strlen(new_team->name) + 100 +
        strlen(new_team->description) + strlen(new_team->uuid)) *sizeof(char));

    sprintf(reply,
    "701 Team \"%s\" with name \"%s\" and description \"%s\" was created.",
        new_team->uuid, new_team->name, new_team->description);
    sprintf(evt_reply,
    "711 Team \"%s\" with name \"%s\" and description \"%s\" was created.",
        new_team->uuid, new_team->name, new_team->description);
    write_to_socket(client->socket, str_concat(reply, CRLF));
    send_notification_to_all(server, str_concat(evt_reply, CRLF));
}

void create_team(server_t *server, char *team_name, char *team_desc,
    client_t *client)
{
    int new_length = get_teams_length(server->database.teams);

    if (team_with_same_name_exists(server->database.teams, team_name)) {
        write_to_socket(client->socket, str_concat(MSG_413, CRLF));
        return;
    }
    server->database.teams = add_new_team(server->database.teams,
        team_name, team_desc, client->uuid);
    server_event_team_created(server->database.teams[new_length]->uuid,
        server->database.teams[new_length]->name,
        server->database.teams[new_length]->creator_uuid);
    save_database(server->database);
    send_create_team_events(server, client,
        server->database.teams[new_length]);
}

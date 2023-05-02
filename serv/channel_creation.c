/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** channel_creation
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "protocol.h"
#include "client_utils.h"
#include "logging_server.h"
#include "str_utils.h"
#include "socket_utils.h"

bool create_channel_has_errors(team_t *team, client_t *client, char *name)
{
    char *msg = NULL;

    if (team == NULL) {
        char *msg = malloc((25 + UUID_LEN) * sizeof(char));
        msg = strcpy(msg, "428 Team \"");
        msg = str_concat(msg, client->context.team_uuid);
        msg = strcpy(msg, "\" not found.");
        write_to_socket(client->socket, str_concat(msg, CRLF));
        return true;
    }
    if (channel_with_same_name_exists(team->channels, name)) {
        write_to_socket(client->socket, str_concat(MSG_413, CRLF));
        return true;
    }
    return false;
}

channel_t **create_channel_on_team(team_t *team, char *client_uuid,
    char *name, char *desc)
{
    int len = get_channels_length(team->channels);

    team->channels = realloc(team->channels, (len + 2) *
        sizeof(struct channel_s *));
    team->channels[len] = malloc(sizeof(struct channel_s));
    team->channels[len]->creator_uuid =
        malloc((strlen(client_uuid) + 1) * sizeof(char));
    team->channels[len]->creator_uuid =
        strcpy(team->channels[len]->creator_uuid, client_uuid);
    team->channels[len]->name = name;
    team->channels[len]->description = desc;
    team->channels[len]->uuid = generate_new_uuid(2);
    team->channels[len]->threads = malloc(1 * sizeof(struct thread_s *));
    team->channels[len]->threads[0] = NULL;
    team->channels[len + 1] = NULL;
    server_event_channel_created(team->uuid, team->channels[len]->uuid, name);
    return team->channels;
}

void send_channel_create_event(server_t *server, client_t *client,
    channel_t *channel, team_t *team)
{
    char *msg = malloc(15 * sizeof(char));
    char *evt_msg = malloc(15 * sizeof(char));

    msg = strcpy(msg, "702 Channel \"");
    msg = str_concat(msg, channel->uuid);
    msg = str_concat(msg, "\" with name \"");
    msg = str_concat(msg, channel->name);
    msg = str_concat(msg, "\" and description \"");
    msg = str_concat(msg, channel->description);
    msg = str_concat(msg, "\" was created.");
    evt_msg = strcpy(evt_msg, "712 Channel \"");
    evt_msg = str_concat(evt_msg, channel->uuid);
    evt_msg = str_concat(evt_msg, "\" with name \"");
    evt_msg = str_concat(evt_msg, channel->name);
    evt_msg = str_concat(evt_msg, "\" and description \"");
    evt_msg = str_concat(evt_msg, channel->description);
    evt_msg = str_concat(evt_msg, "\" was created.");
    write_to_socket(client->socket, str_concat(msg, CRLF));
    send_notification_to_team(server, team, evt_msg, NULL);
}

void create_channel(server_t *server, char *name, char *desc,
    client_t *client)
{
    team_t *team = get_team(server, client->context.team_uuid);
    int last = 0;
    char *msg = malloc(15 * sizeof(char));

    if (create_channel_has_errors(team, client, name))
        return;
    last = get_channels_length(team->channels);
    team->channels = create_channel_on_team(team, client->uuid, name, desc);
    save_database(server->database);
    msg = strcpy(msg, "702 Channel \"");
    msg = str_concat(msg, team->channels[last]->uuid);
    msg = str_concat(msg, "\" with name \"");
    msg = str_concat(msg, team->channels[last]->name);
    msg = str_concat(msg, "\" and description \"");
    msg = str_concat(msg, team->channels[last]->description);
    msg = str_concat(msg, "\" was created.");
    send_channel_create_event(server, client, team->channels[last], team);
}

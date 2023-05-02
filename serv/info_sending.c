/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** info_sending
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "server.h"
#include "protocol.h"
#include "str_utils.h"
#include "client_utils.h"
#include "socket_utils.h"

void send_info_user(server_t *server, client_t *client)
{
    char *dest = malloc(48 * sizeof(char));
    char *tmp_line = malloc((strlen(client->uuid) + strlen(client->user_name)
        + 100) * sizeof(char));

    dest = strcpy(dest, "502 Here is the information for requested user");
    sprintf(tmp_line, " \"%s,%s,%i\"", client->uuid, client->user_name, 1);
    dest = str_concat(dest, tmp_line);
    write_to_socket(client->socket, str_concat(dest, CRLF));
}

void send_info_team(server_t *server, client_t *client)
{
    char *dest = malloc(48 * sizeof(char));
    team_t *team = get_team(server, client->context.team_uuid);
    char *tmp_line = malloc((strlen(team->uuid) + strlen(team->name) +
        strlen(team->description) + 100) * sizeof(char));

    dest = strcpy(dest, "512 Here is the information for requested team");
    sprintf(tmp_line, " \"%s,%s,%s\"", team->uuid, team->name,
        team->description);
    dest = str_concat(dest, tmp_line);
    write_to_socket(client->socket, str_concat(dest, CRLF));
}

void send_info_channel(server_t *server, client_t *client)
{
    team_t *team = get_team(server, client->context.team_uuid);
    channel_t *channel = get_channel_from_team(team,
        client->context.channel_uuid);
    char *dest = malloc(55 * sizeof(char));
    char *tmp_line = malloc((strlen(channel->uuid) + strlen(channel->name) +
        strlen(channel->description) + 100) * sizeof(char));

    dest = strcpy(dest, "513 Here is the information for requested channel ");
    sprintf(tmp_line, " \"%s,%s,%s\"",
        channel->uuid, channel->name, channel->description);
    dest = str_concat(dest, tmp_line);
    write_to_socket(client->socket, str_concat(dest, CRLF));
}

void send_info_thread(server_t *server, client_t *client)
{
    team_t *team = get_team(server, client->context.team_uuid);
    channel_t *channel = get_channel_from_team(team,
        client->context.channel_uuid);
    thread_t *thread = get_thread_from_channel(channel,
        client->context.thread_uuid);
    char *dest = malloc(55 * sizeof(char));
    char *tmp_line = malloc((strlen(thread->uuid) + strlen(
        thread->creator_uuid) + strlen(thread->name) +
        strlen(thread->description) + 100) * sizeof(char));

    dest = strcpy(dest, "514 Here is the information for requested thread ");
    sprintf(tmp_line, " \"%s,%s,%li,%s,%s\"", thread->uuid,
        thread->creator_uuid, thread->timestamp, thread->name,
        thread->description);
    dest = str_concat(dest, tmp_line);
    write_to_socket(client->socket, str_concat(dest, CRLF));
}

void send_info(int client_socket, server_t *server, char *cmd)
{
    client_t *client = get_client(server, client_socket);

    if (use_detect_exists_errors(server, client))
        return;
    if (client->uuid == NULL) {
        write_to_socket(client->socket, str_concat(MSG_403, CRLF));
        return;
    }
    if (client->context.type == TEAM)
        send_info_user(server, client);
    if (client->context.type == CHANNEL)
        send_info_team(server, client);
    if (client->context.type == THREAD)
        send_info_channel(server, client);
    if (client->context.type == REPLY)
        send_info_thread(server, client);
}

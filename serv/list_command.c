/*
** EPITECH PROJECT, 2023
** teams
** File description:
** list_command
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "str_utils.h"
#include "client_utils.h"
#include "protocol.h"
#include "server.h"
#include "socket_utils.h"

void display_teams(server_t *server, client_t *client, int client_socket)
{
    char *dest = "";
    char *tmp_line = NULL;
    char *msg = "503 Here are the informations of the teams";

    for (int i = 0; server->database.teams[i] != NULL; i++) {
        tmp_line = malloc((strlen(server->database.teams[i]->uuid) +
        strlen(server->database.teams[i]->name) +
        strlen(server->database.teams[i]->description) + 100)
        * sizeof(char));
        sprintf(tmp_line, " \"%s,%s,%s\"",
            server->database.teams[i]->uuid,
            server->database.teams[i]->name,
            server->database.teams[i]->description);
        dest = str_concat(dest, tmp_line);
        free(tmp_line);
    }
    write_to_socket(client_socket, str_concat(str_concat(msg, dest), CRLF));
}

void display_channels(server_t *server, client_t *client, int client_socket)
{
    char *dest = "";
    char *msg = "504 Here are the informations of the channels";

    for (int i = 0; server->database.teams[i] != NULL; i++) {
        if (strcmp(server->database.teams[i]->uuid,
        client->context.team_uuid) == 0) {
                dest = get_chan_info(server->database.teams[i]->channels,
                dest);
        }
    }
    write_to_socket(client_socket, str_concat(str_concat(msg, dest),
    CRLF));
}

void display_threads(server_t *server, client_t *client, int client_socket)
{
    char *dest = "";
    char *msg = "505 Here are the informations of the threads";

    for (int i = 0; server->database.teams[i] != NULL; i++) {
        if (strcmp(server->database.teams[i]->uuid,
        client->context.team_uuid) == 0) {
                dest = thread_loop(server, client, dest, i);
        }
    }
    write_to_socket(client_socket, str_concat(str_concat(msg, dest),
    CRLF));
}

void display_replies(server_t *server, client_t *client, int client_socket)
{
    team_t *team = get_team(server, client->context.team_uuid);
    channel_t *channel = get_channel_from_team(team,
        client->context.channel_uuid);
    thread_t *thread = get_thread_from_channel(channel,
        client->context.thread_uuid);
    char *tmp_line = NULL;
    char *msg = malloc(47 * sizeof(char));

    msg = strcpy(msg, "506 Here are the informations of the replies");
    for (int i = 0; thread->replies[i] != NULL; i++) {
        tmp_line = malloc((strlen(thread->uuid) + strlen(
            thread->replies[i]->sender_uuid) + strlen(thread->replies[i]->msg)
            + 100) * sizeof(char));
        sprintf(tmp_line, " \"%s,%s,%li,%s\"",
            thread->uuid, thread->replies[i]->sender_uuid,
            thread->replies[i]->timestamp, thread->replies[i]->msg);
        msg = str_concat(msg, tmp_line);
        free(tmp_line);
    }
    write_to_socket(client_socket, str_concat(msg, CRLF));
}

void list(int client_socket, server_t *server, char *cmd)
{
    client_t *client = get_client(server, client_socket);

    if (use_detect_exists_errors(server, client))
        return;
    if (client->uuid == NULL) {
        write_to_socket(client->socket, str_concat(MSG_403, CRLF));
        return;
    }
    if (client->context.type == TEAM)
        display_teams(server, client, client_socket);
    if (client->context.type == CHANNEL)
        display_channels(server, client, client_socket);
    if (client->context.type == THREAD)
        display_threads(server, client, client_socket);
    if (client->context.type == REPLY)
        display_replies(server, client, client_socket);
}

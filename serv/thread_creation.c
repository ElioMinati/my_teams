/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** thread_creation
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "server.h"
#include "protocol.h"
#include "logging_server.h"
#include "str_utils.h"
#include "socket_utils.h"

bool create_thread_has_errors(team_t *team, channel_t *channel,
    client_t *client, char *name)
{
    char *msg = NULL;

    if (channel == NULL || team == NULL) {
        char *msg = malloc((25 + UUID_LEN) * sizeof(char));
        if (channel == NULL)
            msg = strcpy(msg, "438 Channel \"");
        if (team == NULL)
            msg = strcpy(msg, "428 Team \"");
        msg = str_concat(msg, client->context.team_uuid);
        msg = strcpy(msg, "\" not found.");
        write_to_socket(client->socket, str_concat(msg, CRLF));
        return true;
    }
    if (thread_with_same_name_exists(channel->threads, name)) {
        write_to_socket(client->socket, str_concat(MSG_413, CRLF));
        return true;
    }
    return false;
}

thread_t **create_thread_on_channel(channel_t *channel, char *client_uuid,
    char *name, char *desc)
{
    int len = get_threads_length(channel->threads);

    channel->threads = realloc(channel->threads, (len + 2) *
        sizeof(struct thread_s *));
    channel->threads[len] = malloc(sizeof(struct thread_s));
    channel->threads[len]->creator_uuid =
        malloc((strlen(client_uuid) + 1) * sizeof(char));
    channel->threads[len]->creator_uuid =
        strcpy(channel->threads[len]->creator_uuid, client_uuid);
    channel->threads[len]->name = name;
    channel->threads[len]->description = desc;
    channel->threads[len]->uuid = generate_new_uuid(3);
    channel->threads[len]->replies = malloc(1 * sizeof(struct reply_s *));
    channel->threads[len]->replies[0] = NULL;
    channel->threads[len]->timestamp = time(NULL);
    channel->threads[len + 1] = NULL;
    server_event_thread_created(channel->uuid, channel->threads[len]->uuid,
        client_uuid, name, desc);
    return channel->threads;
}

char *get_create_thread_reply_msg(thread_t *thread)
{
    char *msg_first = malloc((strlen(thread->uuid) + strlen(thread->name)
        + 147) * sizeof(char));
    char *msg_second = malloc((strlen(thread->description) + 36) *
        sizeof(char));

    sprintf(msg_first, "703 Thread \"%s\" with timestamp \"%li\", name \"%s\"",
        thread->uuid, thread->timestamp, thread->name);
    sprintf(msg_second, " and description \"%s\" was created.",
        thread->description);
    return str_concat(msg_first, msg_second);
}

char *get_evt_thread_created_msg(thread_t *thread)
{
    char *msg_first = malloc((strlen(thread->uuid) +
        strlen(thread->creator_uuid) + 147) * sizeof(char));
    char *msg_second = malloc((strlen(thread->description) +
        strlen(thread->name) + 152) * sizeof(char));

    sprintf(msg_first, "713 Thread \"%s\" created by: \"%s\" with timestamp",
        thread->uuid, thread->creator_uuid);
    sprintf(msg_second,
        " \"%li\", name \"%s\" and description \"%s\" was created.",
        thread->timestamp, thread->name, thread->description);
    return str_concat(msg_first, msg_second);
}

void create_thread(server_t *server, char *name, char *desc, client_t *client)
{
    team_t *team = get_team(server, client->context.team_uuid);
    channel_t *channel = get_channel_from_team(team,
        client->context.channel_uuid);
    int last = 0;
    char *msg = NULL;
    char *evt_msg = NULL;

    if (create_thread_has_errors(team, channel, client, name))
        return;
    last = get_threads_length(channel->threads);
    channel->threads = create_thread_on_channel(channel, client->uuid,
        name, desc);
    save_database(server->database);
    msg = get_create_thread_reply_msg(channel->threads[last]);
    evt_msg = get_evt_thread_created_msg(channel->threads[last]);
    write_to_socket(client->socket, str_concat(msg, CRLF));
    send_notification_to_team(server, team, evt_msg, NULL);
}

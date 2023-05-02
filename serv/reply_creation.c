/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** reply_creation
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "protocol.h"
#include "server.h"
#include "logging_server.h"
#include "str_utils.h"
#include "socket_utils.h"

bool create_reply_has_errors(team_t *team, channel_t *channel,
    thread_t *thread, client_t *client)
{
    char *msg = malloc((25 + UUID_LEN) * sizeof(char));

    if (thread == NULL)
        msg = strcpy(msg, "448 Thread \"");
    if (channel == NULL)
        msg = strcpy(msg, "438 Channel \"");
    if (team == NULL)
        msg = strcpy(msg, "428 Team \"");
    if (channel == NULL || team == NULL || thread == NULL) {
        msg = str_concat(msg, client->context.team_uuid);
        msg = strcpy(msg, "\" not found.");
        write_to_socket(client->socket, str_concat(msg, CRLF));
        return true;
    }
    return false;
}

reply_t **create_reply_on_thread(thread_t *thread, char *client_uuid,
    char *msg)
{
    int len = get_replies_length(thread->replies);

    thread->replies = realloc(thread->replies, (len + 2) *
        sizeof(struct reply_s *));
    thread->replies[len] = malloc(sizeof(struct reply_s));
    thread->replies[len]->sender_uuid =
        malloc((strlen(client_uuid) + 1) * sizeof(char));
    thread->replies[len]->sender_uuid =
        strcpy(thread->replies[len]->sender_uuid, client_uuid);
    thread->replies[len]->msg = msg;
    thread->replies[len]->uuid = generate_new_uuid(4);
    thread->replies[len]->timestamp = time(NULL);
    thread->replies[len + 1] = NULL;
    server_event_reply_created(thread->uuid, client_uuid, msg);
    return thread->replies;
}

char *get_create_reply_msg(reply_t *reply, char *team_uuid,
    char *thread_uuid)
{
    char *msg_first = malloc((strlen(team_uuid) + 60) * sizeof(char));
    char *msg_second = malloc((strlen(thread_uuid) +
        strlen(reply->sender_uuid) + strlen(reply->msg) + 35) *
        sizeof(char));

    sprintf(msg_first, "704 Thread reply recieved from team \"%s\" in thread ",
        team_uuid);
    sprintf(msg_second, "\"%s\", from \"%s\" with \"%s\".",
        thread_uuid, reply->sender_uuid, reply->msg);
    return str_concat(msg_first, msg_second);
}

void create_reply(server_t *server, char *msg, client_t *client)
{
    team_t *team = get_team(server, client->context.team_uuid);
    channel_t *channel = get_channel_from_team(team,
        client->context.channel_uuid);
    thread_t *thread = get_thread_from_channel(channel,
        client->context.thread_uuid);
    int last = 0;
    char *reply_msg = NULL;
    char *creator_msg = NULL;
    if (create_reply_has_errors(team, channel, thread, client))
        return;
    last = get_replies_length(thread->replies);
    thread->replies = create_reply_on_thread(thread, client->uuid, msg);
    save_database(server->database);
    reply_msg = get_create_reply_msg(thread->replies[last],
        team->uuid, thread->uuid);
    creator_msg = get_create_reply_for_creator_msg(thread->uuid,
        thread->replies[last]);
    write_to_socket(client->socket, str_concat(creator_msg, CRLF));
    send_notification_to_team(server, team, reply_msg, NULL);
}

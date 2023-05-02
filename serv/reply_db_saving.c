/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** reply_db_saving
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"

char *get_individual_raw_reply(reply_t *reply)
{
    char *raw_line = malloc((strlen(reply->uuid) +
        strlen(reply->sender_uuid) + strlen(reply->msg) + 100)
        * sizeof(char));

    sprintf(raw_line, "\"%s\" \"%s\" \"%s\" \"%li\"", reply->uuid,
        reply->sender_uuid, reply->msg, reply->timestamp);
    return raw_line;
}

void save_replies_from_channel(FILE *stream, channel_t *channel)
{
    for (int i = 0; channel->threads[i] != NULL; i++) {
        for (int j = 0; channel->threads[i]->replies[j] != NULL; j++)
            fprintf(stream, "%s\n", get_individual_raw_reply(
                channel->threads[i]->replies[j]));
    }
}

void save_replies(FILE *stream, team_t **teams)
{
    fprintf(stream, "%s:%s", DB_REPLIES_SECTION, DB_LINE_SEPARATOR);
    for (int i = 0; teams[i] != NULL; i++) {
        for (int j = 0; teams[i]->channels[j] != NULL; j++)
            save_replies_from_channel(stream, teams[i]->channels[j]);
    }
}

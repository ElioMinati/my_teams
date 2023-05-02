/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** thread_db_saving
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "str_utils.h"

char *get_individual_raw_thread(thread_t *thread)
{
    char *raw_line = malloc((strlen(thread->uuid) +
        strlen(thread->creator_uuid) + strlen(thread->name)
        + strlen(thread->description) + 100) * sizeof(char));

    sprintf(raw_line, "\"%s\" \"%s\" \"%s\" \"%s\" \"%li\" \"", thread->uuid,
        thread->creator_uuid, thread->name, thread->description,
        thread->timestamp);
    for (int i = 0; thread->replies[i] != NULL; i++) {
        raw_line = str_concat(raw_line, thread->replies[i]->uuid);
        raw_line = str_concat(raw_line, ",");
    }
    raw_line = str_concat(raw_line, "\"");
    return raw_line;
}

void save_threads_from_channel(FILE *stream, channel_t *channel)
{
    for (int i = 0; channel->threads[i] != NULL; i++)
        fprintf(stream, "%s\n", get_individual_raw_thread(channel->threads[i]));
}

void save_threads(FILE *stream, team_t **teams)
{
    fprintf(stream, "%s:%s", DB_THREADS_SECTION, DB_LINE_SEPARATOR);
    for (int i = 0; teams[i] != NULL; i++) {
        for (int j = 0; teams[i]->channels[j] != NULL; j++)
            save_threads_from_channel(stream, teams[i]->channels[j]);
    }
}

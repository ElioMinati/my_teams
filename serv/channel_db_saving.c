/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** channel_db_saving
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "str_utils.h"

static void save_channel(FILE *stream, channel_t *channel)
{
    char *raw_line = malloc((strlen(channel->uuid) + strlen(channel->name) +
    strlen(channel->creator_uuid) + strlen(channel->description) +
    100) * sizeof(char));
    sprintf(raw_line, "\"%s\" \"%s\" \"%s\" \"%s\" \"", channel->uuid,
        channel->creator_uuid, channel->name, channel->description);
    for (int i = 0; channel->threads[i] != NULL; i++) {
        raw_line = str_concat(raw_line, channel->threads[i]->uuid);
        raw_line = str_concat(raw_line, ",");
    }
    raw_line = str_concat(raw_line, "\"");
    fprintf(stream, "%s\n", raw_line);
}

channel_t **channel_append(channel_t **channels, char **lines, int i,
    char **channel_uuids)
{
    int len = get_channels_length(channels);
    char **full_line = my_str_to_word_array(lines[i], '"');

    if (array_find(channel_uuids, full_line[1]) == NULL)
        return channels;
    channels = realloc(channels, (len + 2) *
        sizeof(struct channel_s *));
    channels[len] = malloc(sizeof(struct channel_s));
    channels[len]->uuid = full_line[1];
    channels[len]->creator_uuid = full_line[3];
    channels[len]->name = full_line[5];
    channels[len]->description = full_line[7];
    channels[len]->threads = get_threads_from_channel(lines, full_line[9]);
    channels[len + 1] = NULL;
    return channels;
}

channel_t **parse_channels(char **lines, char **channel_uuids)
{
    channel_t **channels = malloc(1 * sizeof(struct channel_s *));
    bool at_section = false;

    channels[0] = NULL;
    for (int i = 0; lines[i] != NULL; i++) {
        if (strcmp(lines[i], DB_TABLE_SEPARATOR) == 0) {
            at_section = false;
            continue;
        }
        channels = (at_section ?
            channel_append(channels, lines, i, channel_uuids) : channels);
        if (strcmp(lines[i], str_concat(DB_CHANNELS_SECTION, ":")) == 0)
            at_section = true;
    }
    return channels;
}

void save_channels(FILE *stream, team_t **teams)
{
    fprintf(stream, "%s:%s", DB_CHANNELS_SECTION, DB_LINE_SEPARATOR);
    for (int i = 0; teams[i] != NULL; i++) {
        for (int j = 0; teams[i]->channels[j] != NULL; j++)
            save_channel(stream, teams[i]->channels[j]);
    }
}

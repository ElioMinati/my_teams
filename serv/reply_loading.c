/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** reply_loading
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "str_utils.h"

reply_t **reply_append(reply_t **replies, char **raw_lines, int i,
    char **reply_uuids)
{
    int len = get_replies_length(replies);
    char **full_line = my_str_to_word_array(raw_lines[i], '"');

    if (array_find(reply_uuids, full_line[1]) == NULL)
        return replies;
    replies = realloc(replies, (len + 2) *
        sizeof(struct reply_s *));
    replies[len] = malloc(sizeof(struct reply_s));
    replies[len]->uuid = full_line[1];
    replies[len]->sender_uuid = full_line[3];
    replies[len]->msg = full_line[5];
    replies[len]->timestamp = atol(full_line[7]);
    replies[len + 1] = NULL;
    return replies;
}

reply_t **get_replies_from_thread(char **raw_lines, char *raw_uuids)
{
    reply_t **replies = malloc(1 * sizeof(struct reply_s *));
    char **reply_uuids = my_str_to_word_array(raw_uuids, ',');
    bool at_section = false;

    replies[0] = NULL;
    for (int i = 0; raw_lines[i] != NULL; i++) {
        if (strcmp(raw_lines[i], DB_TABLE_SEPARATOR) == 0) {
            at_section = false;
            continue;
        }
        replies = (at_section ?
            reply_append(replies, raw_lines, i, reply_uuids) : replies);
        if (strcmp(raw_lines[i], str_concat(DB_REPLIES_SECTION, ":")) == 0)
            at_section = true;
    }
    return replies;
}

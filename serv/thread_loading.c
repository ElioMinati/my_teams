/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** thread_loading
*/

#include <string.h>
#include <stdlib.h>
#include "server.h"
#include "str_utils.h"

thread_t **thread_append(thread_t **threads, char **raw_lines, int i,
    char **thread_uuids)
{
    int len = get_threads_length(threads);
    char **full_line = my_str_to_word_array(raw_lines[i], '"');

    if (array_find(thread_uuids, full_line[1]) == NULL)
        return threads;
    threads = realloc(threads, (len + 2) *
        sizeof(struct thread_s *));
    threads[len] = malloc(sizeof(struct thread_s));
    threads[len]->uuid = full_line[1];
    threads[len]->creator_uuid = full_line[3];
    threads[len]->name = full_line[5];
    threads[len]->description = full_line[7];
    threads[len]->timestamp = atol(full_line[9]);
    threads[len]->replies = get_replies_from_thread(raw_lines, full_line[11]);
    threads[len + 1] = NULL;
    return threads;
}

thread_t **get_threads_from_channel(char **raw_lines, char *raw_uuids)
{
    thread_t **threads = malloc(1 * sizeof(struct thread_s *));
    char **thread_uuids = my_str_to_word_array(raw_uuids, ',');
    bool at_section = false;

    threads[0] = NULL;
    for (int i = 0; raw_lines[i] != NULL; i++) {
        if (strcmp(raw_lines[i], DB_TABLE_SEPARATOR) == 0) {
            at_section = false;
            continue;
        }
        threads = (at_section ?
            thread_append(threads, raw_lines, i, thread_uuids) : threads);
        if (strcmp(raw_lines[i], str_concat(DB_THREADS_SECTION, ":")) == 0)
            at_section = true;
    }
    return threads;
}

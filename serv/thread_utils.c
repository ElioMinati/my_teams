/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** thread_utils
*/

#include <string.h>
#include "server.h"

int get_threads_length(thread_t **threads)
{
    int i = 0;

    for (; threads[i] != NULL; i++);
    return i;
}

bool thread_with_same_name_exists(thread_t **threads, char *name)
{
    if (name == NULL)
        return false;
    for (int i = 0; threads[i] != NULL; i++) {
        if (strcmp(threads[i]->name, name) == 0)
            return true;
    }
    return false;
}

thread_t *get_thread_from_channel(channel_t *channel, char *thread_uuid)
{
    if (channel == NULL || thread_uuid == NULL)
        return NULL;
    for (int i = 0; channel->threads[i] != NULL; i++) {
        if (strcmp(channel->threads[i]->uuid, thread_uuid) == 0)
            return channel->threads[i];
    }
    return NULL;
}

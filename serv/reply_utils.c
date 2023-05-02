/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** reply_utils
*/

#include <string.h>
#include <stdlib.h>
#include "server.h"

int get_replies_length(reply_t **replies)
{
    int i = 0;

    for (; replies[i] != NULL; i++);
    return i;
}

char *get_create_reply_for_creator_msg(char *thread_uuid, reply_t *reply)
{
    char *msg = malloc((strlen(thread_uuid) + strlen(reply->msg) + 146) *
        sizeof(char));

    sprintf(msg, "705 Thread \"%s\" reply created at \"%li\": \"%s\".",
        thread_uuid, reply->timestamp, reply->msg);
    return msg;
}

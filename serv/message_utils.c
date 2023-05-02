/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** message_utils
*/

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "str_utils.h"
#include "server.h"

bool is_message_in_conversation(message_t *message, client_t *client,
    char *uuid)
{
    if (client == NULL)
        return false;
    if (strcmp(message->reciever_uuid, uuid) == 0 &&
        strcmp(message->sender_uuid, client->uuid) == 0)
        return true;
    if (strcmp(message->reciever_uuid, client->uuid) == 0 &&
        strcmp(message->sender_uuid, uuid) == 0)
        return true;
    return false;
}

char *get_message_sending_str(char *uuid, char *body)
{
    char *dest = malloc(24 * sizeof(char));

    dest = strcpy(dest, "602 New message from \"");
    dest = str_concat(dest, uuid);
    dest = str_concat(dest, "\": \"");
    dest = str_concat(dest, body);
    dest = str_concat(dest, "\".");
    return dest;
}

char *get_db_raw_line_msg(char *sender, char *reciever, char *msg_body)
{
    char *raw_line = malloc((strlen(reciever) * 2 + strlen(msg_body) + 100)
        * sizeof(char));
    sprintf(raw_line, "%s %s %li \"%s\"", sender, reciever,
        time(NULL), msg_body);
    return raw_line;
}

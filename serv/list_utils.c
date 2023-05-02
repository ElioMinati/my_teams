/*
** EPITECH PROJECT, 2023
** teams
** File description:
** list_utils
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "str_utils.h"
#include "client_utils.h"
#include "protocol.h"
#include "server.h"

char *get_chan_info(channel_t **chanel, char *dest)
{
    char *tmp_line = NULL;

    for (int i = 0; chanel[i] != NULL; i++) {
        tmp_line = malloc((strlen(chanel[i]->name) +
            strlen(chanel[i]->description) + strlen(chanel[i]->uuid) + 100) *
            sizeof(char));
        sprintf(tmp_line, " \"%s,%s,%s\"",
            chanel[i]->uuid,
            chanel[i]->name,
            chanel[i]->description);
        dest = str_concat(dest, tmp_line);
        free(tmp_line);
    }
    return dest;
}

char *get_thread_info(thread_t **thread, char *dest)
{
    char *tmp_line = NULL;

    for (int i = 0; thread[i] != NULL; i++) {
        tmp_line = malloc((strlen(thread[i]->name) +
            strlen(thread[i]->description) + strlen(thread[i]->uuid) +
            strlen(thread[i]->creator_uuid) + 100) *
            sizeof(char));
        sprintf(tmp_line, " \"%s,%s,%li,%s,%s\"",
            thread[i]->uuid,
            thread[i]->creator_uuid,
            thread[i]->timestamp,
            thread[i]->name,
            thread[i]->description);
        dest = str_concat(dest, tmp_line);
        free(tmp_line);
    }
    return dest;
}

char *thread_loop(server_t *server, client_t *client, char *dest, int i)
{
    for (int j = 0; server->database.teams[i]->channels[j] != NULL; j++) {
        if (strcmp(server->database.teams[i]->channels[j]->uuid,
        client->context.channel_uuid) == 0) {
            dest = get_thread_info(
            server->database.teams[i]->channels[j]->threads, dest);
        }
    }
    return dest;
}

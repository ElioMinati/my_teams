/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** user_parsing
*/

#include <string.h>
#include <stdlib.h>
#include "logging_client.h"
#include "server.h"
#include "str_utils.h"

void free_two_strings(char *str1, char *str2)
{
    free(str1);
    free(str2);
}

static void print_user(const char *uuid, const char *username, int status,
    bool single)
{
    if (!single)
        client_print_users(uuid, username, status);
    else
        client_print_user(uuid, username, status);
}

void parse_listed_users(char *raw_result, bool single)
{
    char *beg = NULL;
    char *tmp_uuid = NULL;
    char *tmp_username = NULL;
    char *tmp_comma = NULL;
    while ((beg = strchr(raw_result, '\"')) != NULL) {
        raw_result = raw_result + (int)((beg + 1) - raw_result);
        tmp_uuid = malloc((UUID_LEN + 1) * sizeof(char));
        tmp_username = malloc((MAX_NAME_LENGTH + 1) * sizeof(char));
        tmp_uuid = strncpy(tmp_uuid, beg + 1, (int)((tmp_comma =
            strchr(raw_result, ',')) - raw_result));
        tmp_uuid[UUID_LEN] = '\0';
        raw_result = raw_result + (int)((tmp_comma + 1) - raw_result);
        tmp_username = strncpy(tmp_username, raw_result, (int)((tmp_comma =
            strchr(raw_result, ',')) - raw_result));
        raw_result = raw_result + (int)((tmp_comma + 1) - raw_result);
        print_user(tmp_uuid, tmp_username, atoi(raw_result), single);
        raw_result = raw_result + (int)((strchr(raw_result, '\"') + 1) -
            raw_result);
        free_two_strings(tmp_uuid, tmp_username);
    }
}

void recieve_user_subscribed(client_t *client, char *recieved)
{
    char **full = my_str_to_word_array(recieved, '"');

    client_print_subscribed(client->uuid, full[1]);
    free_array(full);
}

void recieve_user_unsubscribed(client_t *client, char *recieved)
{
    char **full = my_str_to_word_array(recieved, '"');

    client_print_unsubscribed(client->uuid, full[1]);
    free_array(full);
}

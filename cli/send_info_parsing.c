/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** send_info_parsing
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "client.h"
#include "str_utils.h"

void parse_information_from_cmd_to_send(client_t *client, char *cmd)
{
    char **user_full = NULL;

    if (strncmp(cmd, "/login ", 6) == 0 && client->uuid == NULL) {
        user_full = my_str_to_word_array(cmd, '"');
        client->user_name = user_full[1];
    }
}

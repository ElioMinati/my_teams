/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** creation_parsing
*/

#include <stdio.h>
#include <stdlib.h>
#include "logging_client.h"
#include "str_utils.h"

void recieve_team_created(char *recieved)
{
    char **cmd = my_str_to_word_array(recieved, '"');

    if (count_chars(recieved, '"') != 6) {
        printf("ERROR: 701 message format error.\n");
        return;
    }
    client_print_team_created(cmd[1], cmd[3], cmd[5]);
}

void recieve_team_event_created(char *recieved)
{
    char **cmd = my_str_to_word_array(recieved, '"');

    if (count_chars(recieved, '"') != 6) {
        printf("ERROR: 711 message format error.\n");
        return;
    }
    client_event_team_created(cmd[1], cmd[3], cmd[5]);
}

void recieve_channel_event_created(char *recieved)
{
    char **cmd = my_str_to_word_array(recieved, '"');

    if (count_chars(recieved, '"') != 6) {
        printf("ERROR: 712 message format error.\n");
        return;
    }
    client_event_channel_created(cmd[1], cmd[3], cmd[5]);
}

void recieve_thread_event_created(char *recieved)
{
    char **full = my_str_to_word_array(recieved, '"');

    if (count_chars(recieved, '"') != 10) {
        printf("ERROR: 713 message format error.\n");
        return;
    }
    client_event_thread_created(full[1], full[3], atol(full[5]),
        full[7], full[9]);
}

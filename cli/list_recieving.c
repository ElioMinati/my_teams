/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** list_recieving
*/

#include <stdio.h>
#include <stdlib.h>
#include "str_utils.h"
#include "logging_client.h"

void parse_list_teams(char *recieved)
{
    char **full = my_str_to_word_array(recieved, '"');
    char **tmp_team = NULL;

    for (int i = 1; full[i - 1] != NULL && full[i] != NULL; i += 2) {
        tmp_team = my_str_to_word_array(full[i], ',');
        client_print_teams(tmp_team[0], tmp_team[1], tmp_team[2]);
    }
}

void parse_list_channels(char *recieved)
{
    char **full = my_str_to_word_array(recieved, '"');
    char **tmp_chan = NULL;

    for (int i = 1; full[i - 1] != NULL && full[i] != NULL; i += 2) {
        tmp_chan = my_str_to_word_array(full[i], ',');
        client_team_print_channels(tmp_chan[0], tmp_chan[1], tmp_chan[2]);
    }
}

void parse_list_threads(char *recieved)
{
    char **full = my_str_to_word_array(recieved, '"');
    char **tmp_thread = NULL;

    for (int i = 1; full[i - 1] != NULL && full[i] != NULL; i += 2) {
        tmp_thread = my_str_to_word_array(full[i], ',');
        client_channel_print_threads(tmp_thread[0], tmp_thread[1],
            atol(tmp_thread[2]), tmp_thread[3], tmp_thread[4]);
    }
}

void parse_list_replies(char *recieved)
{
    char **full = my_str_to_word_array(recieved, '"');
    char **tmp_thread = NULL;

    for (int i = 1; full[i - 1] != NULL && full[i] != NULL; i += 2) {
        tmp_thread = my_str_to_word_array(full[i], ',');
        client_thread_print_replies(tmp_thread[0], tmp_thread[1],
            atol(tmp_thread[2]), tmp_thread[3]);
    }
}

/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** team_parsing
*/

#include <stdlib.h>
#include "logging_client.h"
#include "str_utils.h"

void parse_team(char *cmd)
{
    char **full_cmd = my_str_to_word_array(cmd, '"');
    char **team_info = my_str_to_word_array(full_cmd[1], ',');

    client_print_team(team_info[0], team_info[1], team_info[2]);
}

void parse_channel(char *cmd)
{
    char **full_cmd = my_str_to_word_array(cmd, '"');
    char **channel_info = my_str_to_word_array(full_cmd[1], ',');

    client_print_channel(channel_info[0], channel_info[1], channel_info[2]);
}

void parse_thread(char *cmd)
{
    char **full_cmd = my_str_to_word_array(cmd, '"');
    char **thread_info = my_str_to_word_array(full_cmd[1], ',');

    client_print_thread(thread_info[0], thread_info[1], atol(thread_info[2]),
        thread_info[3], thread_info[4]);
}

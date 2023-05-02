/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** error_parsing
*/

#include "logging_client.h"
#include "str_utils.h"

void parse_user_not_found(char *cmd)
{
    char **full = my_str_to_word_array(cmd, '"');

    if (count_chars(cmd, '"') != 2)
        return;
    client_error_unknown_user(full[1]);
}

void parse_team_not_found(char *cmd)
{
    char **full = my_str_to_word_array(cmd, '"');

    if (count_chars(cmd, '"') != 2)
        return;
    client_error_unknown_team(full[1]);
}

void parse_channel_not_found(char *cmd)
{
    char **full = my_str_to_word_array(cmd, '"');

    if (count_chars(cmd, '"') != 2)
        return;
    client_error_unknown_channel(full[1]);
}

void parse_thread_not_found(char *cmd)
{
    char **full = my_str_to_word_array(cmd, '"');

    if (count_chars(cmd, '"') != 2)
        return;
    client_error_unknown_thread(full[1]);
}

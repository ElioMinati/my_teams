/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** message_recieve
*/

#include <stdlib.h>
#include "logging_client.h"
#include "str_utils.h"

void recieve_message_history(char *cmd)
{
    char **full_cmd = my_str_to_word_array(cmd, '"');
    char **tmp_raw_msg = NULL;

    if (count_chars(cmd, '"') < 4)
        return;
    for (int i = 3; full_cmd[i - 2] != NULL && full_cmd[i - 1] != NULL &&
        full_cmd[i] != NULL; i += 3) {
        tmp_raw_msg = my_str_to_word_array(full_cmd[i], ',');
        client_private_message_print_messages(tmp_raw_msg[0],
            atol(tmp_raw_msg[1]), full_cmd[i + 1]);
    }
}

void recieve_message(char *cmd)
{
    char **full_cmd = my_str_to_word_array(cmd, '"');

    if (count_chars(cmd, '"') != 4)
        return;
    client_event_private_message_received(full_cmd[1], full_cmd[3]);
}

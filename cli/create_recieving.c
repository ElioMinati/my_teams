/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** create_recieving
*/

#include <stdlib.h>
#include <string.h>
#include "client.h"
#include "str_utils.h"
#include "client_utils.h"
#include "logging_client.h"

void recieve_channel_created(char *recieved)
{
    char **full = my_str_to_word_array(recieved, '"');

    client_print_channel_created(full[1], full[3], full[5]);
}

void recieve_thread_created(char *recieved, client_t *client)
{
    char **full = my_str_to_word_array(recieved, '"');

    client_print_thread_created(full[1], client->uuid, atol(full[3]),
        full[5], full[7]);
}

void recieve_reply_created(char *recieved, client_t *client)
{
    char **full = my_str_to_word_array(recieved, '"');
    client_print_reply_created(full[1], client->uuid, atol(full[3]), full[5]);
}

void recieve_reply(char *recieved)
{
    char **full = my_str_to_word_array(recieved, '"');

    client_event_thread_reply_received(full[1], full[3], full[5], full[7]);
}

void parse_event_recieving(char *recieved)
{
    if (strncmp(recieved, "711 ", 4) == 0)
        recieve_team_event_created(recieved);
    if (strncmp(recieved, "712 ", 4) == 0)
        recieve_channel_event_created(recieved);
    if (strncmp(recieved, "713 ", 4) == 0)
        recieve_thread_event_created(recieved);
}

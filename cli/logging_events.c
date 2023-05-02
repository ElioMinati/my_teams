/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** logging_events
*/

#include "server.h"
#include "str_utils.h"
#include "client_utils.h"
#include "logging_client.h"

void parse_user_logged_in(client_t *client, char *recieved)
{
    client->uuid = parse_uuid_from_server_response(recieved);
    client_event_logged_in(client->uuid, client->user_name);
}

void recieve_event_login(char *recieved)
{
    char **full = my_str_to_word_array(recieved, '"');

    client_event_logged_in(full[1], full[3]);
}

void recieve_event_logout(char *recieved)
{
    char **full = my_str_to_word_array(recieved, '"');

    client_event_logged_out(full[1], full[3]);
}

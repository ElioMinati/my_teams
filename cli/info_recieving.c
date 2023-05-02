/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** info_recieving
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "server.h"
#include "socket_utils.h"
#include "client_utils.h"
#include "str_utils.h"
#include "logging_client.h"

static void parse_errors(client_t *client, char *recieved)
{
    if (strncmp(recieved, "403 ", 4) == 0)
        client_error_unauthorized();
    if (strncmp(recieved, "413 ", 4) == 0)
        client_error_already_exist();
    if (strncmp(recieved, "418 ", 4) == 0)
        parse_user_not_found(recieved);
    if (strncmp(recieved, "428 ", 4) == 0)
        parse_team_not_found(recieved);
    if (strncmp(recieved, "438 ", 4) == 0)
        parse_channel_not_found(recieved);
    if (strncmp(recieved, "448 ", 4) == 0)
        parse_thread_not_found(recieved);
}

static void parse_connection(client_t *client, char *recieved)
{
    if (strncmp(recieved, "207 ", 4) == 0)
        parse_user_logged_in(client, recieved);
    if (strncmp(recieved, "205 ", 4) == 0) {
        client->uuid = parse_uuid_from_server_response(recieved);
        client_event_logged_in(client->uuid, client->user_name);
    }
    if (strncmp(recieved, "211 ", 4) == 0)
        recieve_event_login(recieved);
    if (strncmp(recieved, "212 ", 4) == 0)
        recieve_event_logout(recieved);
    if (strncmp(recieved, "222 ", 4) == 0)
        recieve_user_subscribed(client, recieved);
    if (strncmp(recieved, "223 ", 4) == 0)
        recieve_user_unsubscribed(client, recieved);
    if (strncmp(recieved, "299 ", 4) == 0) {
        client_event_logged_out(client->uuid, client->user_name);
        client->user_name = NULL;
        client->uuid = NULL;
    }
}

static void parse_listing_command(char *recieved)
{
    if (strncmp(recieved, "501 ", 4) == 0)
        parse_listed_users(recieved, false);
    if (strncmp(recieved, "502 ", 4) == 0)
        parse_listed_users(recieved, true);
    if (strncmp(recieved, "511 ", 4) == 0)
        recieve_message_history(recieved);
    if (strncmp(recieved, "512 ", 4) == 0)
        parse_team(recieved);
    if (strncmp(recieved, "513 ", 4) == 0)
        parse_channel(recieved);
    if (strncmp(recieved, "514 ", 4) == 0)
        parse_thread(recieved);
    if (strncmp(recieved, "503 ", 4) == 0)
        parse_list_teams(recieved);
    if (strncmp(recieved, "504 ", 4) == 0)
        parse_list_teams(recieved);
    if (strncmp(recieved, "505 ", 4) == 0)
        parse_list_threads(recieved);
    if (strncmp(recieved, "506 ", 4) == 0)
        parse_list_replies(recieved);
}

static void parse_recieved_command(client_t *client, char *recieved)
{
    parse_errors(client, recieved);
    parse_connection(client, recieved);
    parse_listing_command(recieved);
    if (strncmp(recieved, "602 ", 4) == 0)
        recieve_message(recieved);
    if (strncmp(recieved, "701 ", 4) == 0)
        recieve_team_created(recieved);
    if (strncmp(recieved, "702 ", 4) == 0)
        recieve_channel_created(recieved);
    if (strncmp(recieved, "703 ", 4) == 0)
        recieve_thread_created(recieved, client);
    if (strncmp(recieved, "704 ", 4) == 0)
        recieve_reply(recieved);
    if (strncmp(recieved, "705 ", 4) == 0)
        recieve_reply_created(recieved, client);
    parse_event_recieving(recieved);
}

void recieve_from_server(client_t *client)
{
    char *res = read_string_from_fd(client->socket);

    if (res == NULL) {
        printf("Recieved disconnect from server\n");
        exit(0);
    }
    printf("%s\n", res);
    parse_recieved_command(client, res);
}

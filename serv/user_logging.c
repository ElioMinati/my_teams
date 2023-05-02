/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** user_logging
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "server.h"
#include "protocol.h"
#include "str_utils.h"
#include "client_utils.h"
#include "logging_server.h"
#include "socket_utils.h"

static void write_logging_message_to_client(int client_socket, char *uuid,
    int msg_code)
{
    char *msg_content = malloc(12 * sizeof(char));
    if (msg_code == 207) {
        msg_content = strcpy(msg_content, "207 User \"");
        msg_content = str_concat(msg_content, uuid);
        msg_content = str_concat(msg_content, "\" logged in succesfully.");
    } else if (msg_code == 205) {
        msg_content = strcpy(msg_content, "205 User \"");
        msg_content = str_concat(msg_content, uuid);
        msg_content = str_concat(msg_content, "\" created successfully.");
    }
    write_to_socket(client_socket, str_concat(msg_content, CRLF));
}

static bool register_user(server_t *server, char *user_name, int client_socket)
{
    client_t *requested_client = get_client(server, client_socket);

    if (requested_client->uuid == NULL) {
        requested_client->uuid = generate_new_uuid(0);
        requested_client->user_name = malloc((strlen(user_name) + 1) *
            sizeof(char));
        strcpy(requested_client->user_name, user_name);
        register_client_to_db(*requested_client, &server->database);
        write_logging_message_to_client(client_socket, requested_client->uuid,
            205);
        server_event_user_created(requested_client->uuid,
            requested_client->user_name);
        server_event_user_logged_in(requested_client->uuid);
    } else {
        write_to_socket(client_socket, str_concat(MSG_412, CRLF));
        return false;
    }
    return true;
}

static bool login_actual_user(server_t *server, char *user_name,
    int client_socket)
{
    client_t *requested_client = get_client(server, client_socket);
    client_db_t *usr = get_user_from_db(server->database.registered_clients,
        user_name);

    if (requested_client->uuid == NULL && !is_user_uuid_alread_logged_in(
        server, usr->uuid)) {
        requested_client->user_name = malloc((strlen(user_name) + 1) *
            sizeof(char));
        strcpy(requested_client->user_name, user_name);
        requested_client->uuid = malloc((strlen(usr->uuid) + 1) * sizeof(char));
        strcpy(requested_client->uuid, usr->uuid);
        write_logging_message_to_client(client_socket, requested_client->uuid,
            207);
        server_event_user_logged_in(requested_client->uuid);
    } else {
        write_to_socket(client_socket, str_concat(MSG_412, CRLF));
        return false;
    }
    return true;
}

void login_user(int client_socket, server_t *server, char *cmd)
{
    char **full_cmd = my_str_to_word_array(cmd, '\"');
    bool send = true;

    if (full_cmd[1] == NULL || (count_chars(cmd, '\"') != 2)) {
        write_to_socket(client_socket, str_concat(MSG_405, CRLF));
        return;
    }
    if (strchr(full_cmd[1], '\"') != NULL || strchr(full_cmd[1], ',') != NULL) {
        write_to_socket(client_socket, str_concat(MSG_415, CRLF));
        return;
    }
    if (get_user_from_db(server->database.registered_clients, full_cmd[1])
        == NULL)
        send = register_user(server, full_cmd[1], client_socket);
    else
        send = login_actual_user(server, full_cmd[1], client_socket);
    if (send)
        send_user_logged_in_event(server, client_socket);
}

void help(int client_socket, server_t *server, char *cmd)
{
    (void)server;
    (void)cmd;
    write_to_socket(client_socket, str_concat(MSG_300, CRLF));
}

/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** message_commands
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "str_utils.h"
#include "protocol.h"
#include "server.h"
#include "logging_server.h"
#include "client_utils.h"
#include "socket_utils.h"

static bool cmd_list_msg_has_errors(int client_socket, char **cmd_full,
    char *cmd, server_t *server)
{
    if (get_client(server, client_socket)->uuid == NULL) {
        write_to_socket(client_socket, str_concat(MSG_403, CRLF));
        return true;
    }
    if (cmd_full[1] == NULL || count_chars(cmd, '"') != 2) {
        write_to_socket(client_socket, str_concat(MSG_405, CRLF));
        return true;
    }
    if (get_db_client_by_uuid(server->database, cmd_full[1]) == NULL) {
        send_418_to_client(client_socket, cmd_full[1]);
        return true;
    }
    return false;
}

static bool cmd_send_msg_has_errors(int client_socket, char **cmd_full,
    char *cmd, server_t *server)
{
    if (get_client(server, client_socket)->uuid == NULL) {
        write_to_socket(client_socket, str_concat(MSG_403, CRLF));
        return true;
    }
    if (cmd_full[1] == NULL || count_chars(cmd, '"') != 4) {
        write_to_socket(client_socket, str_concat(MSG_405, CRLF));
        return true;
    }
    if (get_db_client_by_uuid(server->database, cmd_full[1]) == NULL) {
        send_418_to_client(client_socket, cmd_full[1]);
        return true;
    }
    return false;
}

void send_message(int client_socket, server_t *server, char *cmd)
{
    char **cmd_full = my_str_to_word_array(cmd, '"');
    char *raw_line = NULL;
    char *msg_to_send = NULL;
    client_t *current = get_client(server, client_socket);
    client_t *send_to = NULL;

    if (cmd_send_msg_has_errors(client_socket, cmd_full, cmd, server))
        return;
    raw_line = get_db_raw_line_msg(current->uuid, cmd_full[1], cmd_full[3]);
    server->database.exchanged_messages = message_log_append(
        server->database.exchanged_messages, raw_line);
    save_database(server->database);
    server_event_private_message_sended(current->uuid, cmd_full[1],
        cmd_full[3]);
    send_to = get_client_by_uuid(server, cmd_full[1]);
    if (send_to != NULL) {
        msg_to_send = get_message_sending_str(current->uuid, cmd_full[3]);
        write_to_socket(send_to->socket, str_concat(msg_to_send, CRLF));
    }
}

static char *get_parsed_msg(message_t *msg)
{
    char *msg_str = malloc((strlen(msg->sender_uuid) +
        strlen(msg->msg) + 100) * sizeof(char));

    sprintf(msg_str, " \"%s,%li,\"%s\"", msg->sender_uuid,
        msg->timestamp, msg->msg);
    return msg_str;
}

void list_messages(int client_socket, server_t *server, char *cmd)
{
    char *dest = malloc(44 * sizeof(char));
    char **cmd_full = my_str_to_word_array(cmd, '"');
    char *tmp_msg = NULL;

    if (cmd_list_msg_has_errors(client_socket, cmd_full, cmd, server))
        return;
    dest = strcpy(dest, "511 Here is the conversation history with ");
    dest = str_concat(dest, "\"");
    dest = str_concat(dest, cmd_full[1]);
    dest = str_concat(dest, "\"");
    for (int i = 0; server->database.exchanged_messages[i] != NULL; i++) {
        if (is_message_in_conversation(server->database.exchanged_messages[i],
        get_client(server, client_socket), cmd_full[1]))
            dest = str_concat(dest, get_parsed_msg(
            server->database.exchanged_messages[i]));
    }
    write_to_socket(client_socket, str_concat(dest, CRLF));
}

/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** create_context
*/

#include <unistd.h>
#include <string.h>
#include "server.h"
#include "str_utils.h"
#include "protocol.h"
#include "client_utils.h"
#include "socket_utils.h"

bool create_has_errors(client_t *client, char **cmd, char *raw_cmd)
{
    context_type_t type = client->context.type;
    if (client->uuid == NULL) {
        write_to_socket(client->socket, str_concat(MSG_403, CRLF));
        return true;
    }
    if (count_chars(raw_cmd, '"') != 4 && (type == TEAM || type == CHANNEL ||
        type == THREAD)) {
        write_to_socket(client->socket, str_concat(MSG_405, CRLF));
        return true;
    }
    if (count_chars(raw_cmd, '"') != 2 && type == REPLY) {
        write_to_socket(client->socket, str_concat(MSG_405, CRLF));
        return true;
    }
    if (count_chars(raw_cmd, '"') == 4 && (strlen(cmd[1]) > MAX_NAME_LENGTH ||
        strlen(cmd[3]) > MAX_BODY_LENGTH)) {
        write_to_socket(client->socket, str_concat(MSG_405, CRLF));
        return true;
    }
    return false;
}

void create_with_context(int client_socket, server_t *server, char *cmd)
{
    client_t *client = get_client(server, client_socket);
    char **seperated = my_str_to_word_array(cmd, '"');

    if (create_has_errors(client, seperated, cmd))
        return;
    if (use_detect_exists_errors(server, client))
        return;
    if (client->context.type == TEAM)
        create_team(server, seperated[1], seperated[3], client);
    if (client->context.type == CHANNEL)
        create_channel(server, seperated[1], seperated[3], client);
    if (client->context.type == THREAD)
        create_thread(server, seperated[1], seperated[3], client);
    if (client->context.type == REPLY)
        create_reply(server, seperated[1], client);
}

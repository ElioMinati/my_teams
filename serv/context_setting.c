/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** context_setting
*/

#include <unistd.h>
#include <string.h>
#include "server.h"
#include "protocol.h"
#include "client_utils.h"
#include "str_utils.h"
#include "socket_utils.h"

bool set_context_for_client(client_t *client, char *team_uuid,
    char *channel_uuid, char *thread_uuid)
{
    client->context.team_uuid = team_uuid;
    client->context.channel_uuid = channel_uuid;
    client->context.thread_uuid = thread_uuid;
    if (team_uuid == NULL)
        client->context.type = TEAM;
    if (team_uuid != NULL && channel_uuid == NULL)
        client->context.type = CHANNEL;
    if (channel_uuid != NULL && thread_uuid == NULL)
        client->context.type = THREAD;
    if (channel_uuid != NULL && thread_uuid != NULL)
        client->context.type = REPLY;
    return true;
}

bool context_cmd_had_errors(int client_socket, server_t *server, int nb_quotes)
{
    if (get_client(server, client_socket)->uuid == NULL) {
        write_to_socket(client_socket, str_concat(MSG_403, CRLF));
        return true;
    }
    if (nb_quotes != 0 && nb_quotes != 2 && nb_quotes != 4 && nb_quotes != 6) {
        write_to_socket(client_socket, str_concat(MSG_405, CRLF));
        return true;
    }
    return false;
}

bool use_detect_exists_errors(server_t *server, client_t *client)
{
    char *msg = NULL;
    if (client->context.team_uuid != NULL &&
        !does_team_uuid_exist(server, client->context.team_uuid))
        msg = str_concat(str_concat(str_concat("428 Team \"",
        client->context.team_uuid), "\" not found."), CRLF);
    if (client->context.channel_uuid != NULL &&
        !does_channel_uuid_exist(server, client->context.team_uuid ,
        client->context.channel_uuid))
        msg = str_concat(str_concat(str_concat("438 Channel \"",
        client->context.channel_uuid), "\" not found."), CRLF);
    if (client->context.thread_uuid != NULL &&
        !does_thread_uuid_exist(server, client->context.team_uuid ,
        client->context.channel_uuid, client->context.thread_uuid))
        msg = str_concat(str_concat(str_concat("448 Thread \"",
        client->context.thread_uuid), "\" not found."), CRLF);
    if (msg != NULL) {
        write_to_socket(client->socket, msg);
        return true;
    }
    return false;
}

void set_context(int client_socket, server_t *server, char *cmd)
{
    char **seperated = my_str_to_word_array(cmd, '"');
    int nb_quotes = count_chars(cmd, '"');
    bool has_err = false;
    client_t *client = get_client(server, client_socket);

    if (context_cmd_had_errors(client_socket, server, nb_quotes))
        return;
    if (nb_quotes == 0)
        has_err = set_context_for_client(client, NULL, NULL, NULL);
    if (nb_quotes == 2)
        has_err = set_context_for_client(client, seperated[1], NULL, NULL);
    if (nb_quotes == 4)
        has_err = set_context_for_client(client, seperated[1], seperated[3],
            NULL);
    if (nb_quotes == 6)
        has_err = set_context_for_client(client, seperated[1], seperated[3],
            seperated[5]);
    write_to_socket(client->socket, str_concat(MSG_300, CRLF));
}

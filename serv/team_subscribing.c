/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** team_subscribing
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "client_utils.h"
#include "str_utils.h"
#include "protocol.h"
#include "logging_server.h"
#include "socket_utils.h"

static bool subscribe_to_team_has_errors(server_t *server, client_t *client,
    char *cmd, char **full_cmd)
{
    char *msg = NULL;

    if (client->uuid == NULL) {
        write_to_socket(client->socket, str_concat(MSG_403, CRLF));
        return true;
    }
    if (count_chars(cmd, '"') != 2) {
        write_to_socket(client->socket, str_concat(MSG_405, CRLF));
        return true;
    }
    if (!does_team_uuid_exist(server, full_cmd[1])) {
        msg = str_concat(str_concat(str_concat("428 Team \"",
        full_cmd[1]), "\" not found."), CRLF);
        write_to_socket(client->socket, msg);
        return true;
    }
    return false;
}

void subscribe_to_team(int client_socket, server_t *server, char *cmd)
{
    client_t *client = get_client(server, client_socket);
    team_t *team = NULL;
    char **full_cmd = my_str_to_word_array(cmd, '"');
    char *msg = NULL;

    if (subscribe_to_team_has_errors(server, client, cmd, full_cmd))
        return;
    team = get_team(server, full_cmd[1]);
    if (array_find(get_team(server, full_cmd[1])->subscribed_users_uuid,
        client->uuid) == NULL) {
        team->subscribed_users_uuid = array_append(team->subscribed_users_uuid,
            client->uuid);
        save_database(server->database);
    }
    server_event_user_subscribed(team->uuid, client->uuid);
    msg = malloc(44 * sizeof(char));
    msg = strcpy(msg, "222 User successfully subscribed to team \"");
    msg = str_concat(msg, team->uuid);
    write_to_socket(client->socket, str_concat(msg, CRLF));
}

void unsubscribe_from_team(int client_socket, server_t *server, char *cmd)
{
    client_t *client = get_client(server, client_socket);
    team_t *team = NULL;
    char **full_cmd = my_str_to_word_array(cmd, '"');
    char *msg = NULL;

    if (subscribe_to_team_has_errors(server, client, cmd, full_cmd))
        return;
    team = get_team(server, full_cmd[1]);
    if (array_find(get_team(server, full_cmd[1])->subscribed_users_uuid,
        client->uuid) != NULL) {
        array_remove(team->subscribed_users_uuid, client->uuid);
        save_database(server->database);
    }
    server_event_user_unsubscribed(team->uuid, client->uuid);
    msg = malloc(48 * sizeof(char));
    msg = strcpy(msg, "223 User successfully unsubscribed from team \"");
    msg = str_concat(msg, team->uuid);
    write_to_socket(client->socket, str_concat(msg, CRLF));
}

/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** subscribed_sending
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "protocol.h"
#include "client_utils.h"
#include "str_utils.h"
#include "socket_utils.h"

void list_teams_subscribed_to(server_t *server, client_t *client)
{
    char *dest = malloc(45 * sizeof(char));
    char *tmp_line = NULL;

    dest = strcpy(dest, "503 Here are the informations of the teams");
    for (int i = 0; server->database.teams[i] != NULL; i++) {
        if (is_user_subscribed_to_team(server->database.teams[i],
            client->uuid)) {
            tmp_line = malloc((strlen(server->database.teams[i]->uuid) +
                strlen(server->database.teams[i]->name) + strlen(
                server->database.teams[i]->description) + 10) * sizeof(char));
            sprintf(tmp_line, " \"%s,%s,%s\"",
                server->database.teams[i]->uuid,
                server->database.teams[i]->name,
                server->database.teams[i]->description);
            dest = str_concat(dest, tmp_line);
            free(tmp_line);
        }
    }
    write_to_socket(client->socket, str_concat(dest, CRLF));
}

char *get_subscribed_users_msg(server_t *server, team_t *team)
{
    char *dest = malloc(45 * sizeof(char));
    char *tmp_line = NULL;
    client_db_t *tmp_user = NULL;

    dest = strcpy(dest, "501 Here are the informations of the users");
    for (int i = 0; team->subscribed_users_uuid[i] != NULL; i++) {
        tmp_line = malloc((MAX_NAME_LENGTH + UUID_LEN + 10) * sizeof(char));
        tmp_user = get_db_client_by_uuid(server->database,
            team->subscribed_users_uuid[i]);
        sprintf(tmp_line, " \"%s,%s,%i\"", tmp_user->uuid, tmp_user->user_name,
            is_client_connected_by_uuid(server->clients_connected,
                server->nb_clients_connected, tmp_user->uuid));
        dest = str_concat(dest, tmp_line);
        free(tmp_line);
    }
    return dest;
}

void list_susbcribed_users(server_t *server, client_t *client, char *team_uuid)
{
    team_t *team = get_team(server, team_uuid);
    client_db_t *tmp_user = NULL;
    char *msg = NULL;
    char *tmp_line;
    char *dest = NULL;

    if (team == NULL) {
        msg = malloc((25 + UUID_LEN) * sizeof(char));
        msg = strcpy(msg, "428 Team \"");
        msg = str_concat(msg, client->context.team_uuid);
        msg = strcpy(msg, "\" not found.");
        write_to_socket(client->socket, str_concat(msg, CRLF));
        return;
    }
    dest = get_subscribed_users_msg(server, team);
    write_to_socket(client->socket, str_concat(dest, CRLF));
}

void send_subscribed(int client_socket, server_t *server, char *cmd)
{
    client_t *client = get_client(server, client_socket);
    char **full_cmd = my_str_to_word_array(cmd, '"');

    if (client->uuid == NULL) {
        write_to_socket(client->socket, str_concat(MSG_403, CRLF));
        return;
    }
    if (count_chars(cmd, '"') != 0 && count_chars(cmd, '"') != 2) {
        write_to_socket(client_socket, str_concat(MSG_405, CRLF));
        return;
    }
    if (count_chars(cmd, '"') == 0)
        list_teams_subscribed_to(server, client);
    else
        list_susbcribed_users(server, client, full_cmd[1]);
}

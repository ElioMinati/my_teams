/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** user_listing
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "str_utils.h"
#include "client_utils.h"
#include "protocol.h"
#include "server.h"
#include "socket_utils.h"

void list_users(int client_socket, server_t *server, char *cmd)
{
    char *dest = malloc(44 * sizeof(char));
    char *tmp_line = NULL;
    if (get_client(server, client_socket)->uuid == NULL) {
        write_to_socket(client_socket, str_concat(MSG_403, CRLF));
        return;
    }
    dest = strcpy(dest, "501 Here are the informations of the users");
    for (int i = 0; server->database.registered_clients[i] != NULL; i++) {
        tmp_line = malloc((UUID_LEN + MAX_NAME_LENGTH + 10) * sizeof(char));
        sprintf(tmp_line, " \"%s,%s,%i\"",
            server->database.registered_clients[i]->uuid,
            server->database.registered_clients[i]->user_name,
            is_client_connected_by_uuid(server->clients_connected,
            server->nb_clients_connected,
            server->database.registered_clients[i]->uuid));
        dest = str_concat(dest, tmp_line);
        free(tmp_line);
    }
    write_to_socket(client_socket, str_concat(dest, CRLF));
}

static bool get_user_info_has_errors(int client_socket, server_t *server,
    char **cmd_array, char *cmd)
{
    if (get_client(server, client_socket)->uuid == NULL) {
        write_to_socket(client_socket, str_concat(MSG_403, CRLF));
        return true;
    }
    if (cmd_array[1] == NULL || (count_chars(cmd, '\"') != 2)) {
        write_to_socket(client_socket, str_concat(MSG_405, CRLF));
        return true;
    }
    return false;
}

void get_user_info(int client_socket, server_t *server, char *cmd)
{
    char *dest = malloc(48 * sizeof(char));
    char *tmp_line = malloc((UUID_LEN + MAX_NAME_LENGTH + 10) * sizeof(char));
    char **cmd_array = my_str_to_word_array(cmd, '\"');
    client_db_t *requested_client = NULL;

    if (get_user_info_has_errors(client_socket, server, cmd_array, cmd))
        return;
    requested_client = get_db_client_by_uuid(server->database, cmd_array[1]);
    if (requested_client == NULL) {
        send_418_to_client(client_socket, cmd_array[1]);
        return;
    }
    dest = strcpy(dest, "502 Here is the information for requested user");
    sprintf(tmp_line, " \"%s,%s,%i\"",
            requested_client->uuid, requested_client->user_name,
            is_client_connected_by_uuid(server->clients_connected,
            server->nb_clients_connected, requested_client->uuid));
    dest = str_concat(dest, tmp_line);
    write_to_socket(client_socket, str_concat(dest, CRLF));
}

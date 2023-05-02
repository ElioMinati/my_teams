/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** client_command_parsing
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"
#include "client_utils.h"
#include "socket_utils.h"
#include "protocol.h"
#include "str_utils.h"
#include "server_commands.h"

static void parse_client_command(int client_socket, server_t *server,
    char *user_cmd)
{
    for (int i = 0; i < NB_CMDS; i++) {
        if (strncmp(user_cmd, command_list[i].name,
            strlen(command_list[i].name)) == 0) {
            (*command_list[i].handle)(client_socket, server, user_cmd);
            return;
        }
    }
    write_to_socket(client_socket, str_concat(MSG_404, CRLF));
    return;
}

void parse_command_for_client(server_t *server, int client_socket)
{
    char *user_cmd = read_string_from_fd(client_socket);

    if (user_cmd == NULL) {
        disconnect_client(server, client_socket, true);
    } else {
        parse_client_command(client_socket, server, user_cmd);
        free(user_cmd);
    }
}

/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** command_sending
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "server.h"
#include "client_utils.h"
#include "str_utils.h"
#include "socket_utils.h"

void parse_and_send_to_server(client_t *client)
{
    char *line = NULL;
    size_t len = 0;

    getline(&line, &len, stdin);
    parse_information_from_cmd_to_send(client, line);
    write_to_socket(client->socket, str_concat(line, CRLF));
}

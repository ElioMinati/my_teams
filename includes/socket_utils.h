/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** socket_utils
*/

#ifndef SOCKET_UTILS_H_
    #define SOCKET_UTILS_H_
    #include "server.h"

void reset_file_descriptors(server_t *server);

void reset_client_file_descriptors(client_t *client);

char *read_string_from_fd(int fd);

void write_to_socket(int sock, char *buf);

#endif /* !SOCKET_UTILS_H_ */

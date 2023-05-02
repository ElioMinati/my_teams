/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_
    #include <arpa/inet.h>
    #include <sys/select.h>
    #include <stdbool.h>
    #define UUID_CHARS "1234567890ABCDEF"
    #define UUID_LEN 37

typedef enum {
    TEAM,
    CHANNEL,
    THREAD,
    REPLY

} context_type_t;

typedef struct context_s {
    context_type_t type;
    char *team_uuid;
    char *channel_uuid;
    char *thread_uuid;
} context_t;

typedef struct client_s {
    int socket;
    char *uuid;
    char *user_name;
    struct sockaddr_in address;
    fd_set read_fds;
    bool disconnect;
    context_t context;
} client_t;

int launch_client(const char *, int);

void parse_and_send_to_server(client_t *client);

void recieve_from_server(client_t *client);

void handle_client_select(client_t *client);

#endif /* !CLIENT_H_ */

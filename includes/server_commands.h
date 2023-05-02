/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** server_commands
*/

#ifndef SERVER_COMMANDS_H_
    #define SERVER_COMMANDS_H_
    #include "server.h"
    #define NB_CMDS 14

void login_user(int client_socket, server_t *server, char *cmd);

void logout_user(int client_socket, server_t *server, char *cmd);

void help(int client_socket, server_t *server, char *cmd);

void list_users(int client_socket, server_t *server, char *cmd);

void get_user_info(int client_socket, server_t *server, char *cmd);

void send_message(int client_socket, server_t *server, char *cmd);

void list_messages(int client_socket, server_t *server, char *cmd);

void set_context(int client_socket, server_t *server, char *cmd);

void create_with_context(int client_socket, server_t *server, char *cmd);

void subscribe_to_team(int client_socket, server_t *server, char *cmd);

void unsubscribe_from_team(int client_socket, server_t *server, char *cmd);

void list(int client_socket, server_t *server, char *cmd);

void send_info(int client_socket, server_t *server, char *cmd);

void send_subscribed(int client_socket, server_t *server, char *cmd);

typedef struct command_s {
    char *name;
    void (*handle)(int, server_t *, char *);
} command_t;

static const command_t command_list[] = {
    {"/login ", &login_user},
    {"/logout", &logout_user},
    {"/users", &list_users},
    {"/user ", &get_user_info},
    {"/send ", &send_message},
    {"/messages ", &list_messages},
    {"/help", &help},
    {"/use", &set_context},
    {"/create ", &create_with_context},
    {"/list", &list},
    {"/subscribe ", &subscribe_to_team},
    {"/unsubscribe ", &unsubscribe_from_team},
    {"/info", &send_info},
    {"/subscribed", &send_subscribed}
};

#endif /* !SERVER_COMMANDS_H_ */

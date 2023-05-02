/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** client_utils
*/

#ifndef CLIENT_UTILS_H_
    #define CLIENT_UTILS_H_
    #include "server.h"

bool is_client_connected(client_t *clients, int nb_clients,
    int client_socket);

void accept_new_client(server_t *server);

client_t *get_client(server_t *server, int client_socket);

void parse_command_for_client(server_t *server, int client_socket);

void disconnect_client(server_t *server, int client_socket, bool kill);

client_db_t *get_user_from_db(client_db_t **registered, char *user_name);

void parse_information_from_cmd_to_send(client_t *client, char *cmd);

int is_client_connected_by_uuid(client_t *clients, int nb_clients, char *uuid);

void parse_listed_users(char *raw_result, bool single);

client_db_t *get_db_client_by_uuid(server_db_t database, char *uuid);

bool is_message_in_conversation(message_t *message, client_t *client,
    char *uuid);

void send_418_to_client(int client_socket, char *uuid_not_found);

void parse_user_not_found(char *cmd);

client_t *get_client_by_uuid(server_t *server, char *uuid);

void recieve_message(char *cmd);

void recieve_message_history(char *cmd);

char *get_db_raw_line_msg(char *sender, char *reciever, char *msg_body);

char *get_message_sending_str(char *uuid, char *body);

void recieve_team_created(char *recieved);

void recieve_user_subscribed(client_t *client, char *recieved);

void recieve_user_unsubscribed(client_t *client, char *recieved);

void recieve_channel_created(char *recieved);

void recieve_thread_created(char *recieved, client_t *client);

void recieve_reply_created(char *recieved, client_t *client);

void recieve_reply(char *recieved);

void parse_team_not_found(char *cmd);

void parse_channel_not_found(char *cmd);

void parse_thread_not_found(char *cmd);

void parse_team(char *cmd);

void recieve_team_event_created(char *recieved);

void recieve_channel_event_created(char *recieved);

void recieve_thread_event_created(char *recieved);

void parse_event_recieving(char *recieved);

void parse_list_teams(char *recieved);

void parse_list_channels(char *recieved);

void parse_list_threads(char *recieved);

void recieve_event_login(char *recieved);

void recieve_event_logout(char *recieved);

void parse_user_logged_in(client_t *client, char *recieved);

void parse_list_replies(char *recieved);

void parse_channel(char *cmd);

void parse_thread(char *cmd);

#endif /* !CLIENT_UTILS_H_ */

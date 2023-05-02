/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** server
*/

#ifndef SERVER_H_
    #include <stdio.h>
    #define SERVER_H_
    #define MAX_CLIENTS 150
    #define MAX_NAME_LENGTH 32
    #define MAX_BODY_LENGTH 512
    #define CRLF "\r\n"
    #define DB_PATH "server.db"
    #define DB_USER_SECTION "registered_clients"
    #define DB_MSG_SECTION "message_logs"
    #define DB_TEAMS_SECTION "teams"
    #define DB_CHANNELS_SECTION "channels"
    #define DB_THREADS_SECTION "threads"
    #define DB_REPLIES_SECTION "replies"
    #define DB_LINE_SEPARATOR "\n"
    #define DB_TABLE_SEPARATOR "---------------------------------------------"
    #include "client.h"

typedef struct message_s {
    char *sender_uuid;
    char *reciever_uuid;
    char *msg;
    time_t timestamp;
} message_t;

typedef struct reply_s {
    char *uuid;
    char *sender_uuid;
    char *msg;
    time_t timestamp;
} reply_t;

typedef struct thread_s {
    char *name;
    char *uuid;
    char *creator_uuid;
    char *description;
    time_t timestamp;
    reply_t **replies;
} thread_t;

typedef struct channel_s {
    char *name;
    char *uuid;
    char *creator_uuid;
    char *description;
    thread_t **threads;
} channel_t;

typedef struct team_s {
    char *name;
    char *uuid;
    char *creator_uuid;
    char *description;
    channel_t **channels;
    char **subscribed_users_uuid;
} team_t;

typedef struct client_db_s {
    char *user_name;
    char *uuid;
} client_db_t;

typedef struct server_db_s {
    client_db_t **registered_clients;
    message_t **exchanged_messages;
    team_t **teams;
} server_db_t;

typedef struct server_s {
    int socket;
    struct sockaddr_in address;
    fd_set read_fds;
    client_t *clients_connected;
    char **registered_client_uuids;
    int nb_clients_connected;
    server_db_t database;
} server_t;

server_db_t load_database(void);

void save_database(server_db_t db);

int db_user_len(client_db_t **clients);

void register_client_to_db(client_t client, server_db_t *db);

client_db_t **parse_users(char *raw_file);

message_t **message_log_append(message_t **messages, char *raw_line);

message_t **parse_sent_messages(char *raw_file);

void save_messages(FILE *stream, message_t **exchanged_messages);

void save_users(FILE *stream, client_db_t **users);

void start_server(int port);

void handle_select(server_t *server);

bool does_team_uuid_exist(server_t *server, char *uuid);

bool does_channel_uuid_exist(server_t *server, char *team_uuid, char *uuid);

void create_team(server_t *server, char *team_name, char *team_desc,
    client_t *client);

void save_teams(FILE *stream, team_t **teams);

void save_channels(FILE *stream, team_t **teams);

void save_threads(FILE *stream, team_t **teams);

void save_replies(FILE *stream, team_t **teams);

int get_teams_length(team_t **teams);

team_t **parse_teams(char *raw_file);

bool team_with_same_name_exists(team_t **teams, char *name);

bool channel_with_same_name_exists(channel_t **channels, char *name);

team_t *get_team(server_t *server, char *uuid);

int get_channels_length(channel_t **channels);

channel_t **parse_channels(char **lines, char **channel_uuids);

void create_channel(server_t *server, char *name, char *desc,
    client_t *client);

int get_threads_length(thread_t **threads);

int get_replies_length(reply_t **replies);

thread_t **get_threads_from_channel(char **raw_lines, char *raw_uuids);

reply_t **get_replies_from_thread(char **raw_lines, char *raw_uuids);

channel_t *get_channel_from_team(team_t *team, char *channel_uuid);

bool thread_with_same_name_exists(thread_t **threads, char *name);

void create_thread(server_t *server, char *name, char *desc, client_t *client);

thread_t *get_thread_from_channel(channel_t *channel, char *thread_uuid);

void create_reply(server_t *server, char *msg, client_t *client);

bool does_thread_uuid_exist(server_t *server, char *team_uuid,
    char *channel_uuid, char *uuid);

void send_notification_to_team(server_t *server, team_t *team,
    char *msg_to_send, char *uuid_exempt);

char *get_create_reply_for_creator_msg(char *thread_uuid, reply_t *reply);

bool is_user_uuid_alread_logged_in(server_t *server, char *uuid);

char *get_chan_info(channel_t **chanel, char *dest);

char *thread_loop(server_t *server,
client_t *client, char *dest, int i);

bool use_detect_exists_errors(server_t *server, client_t *client);

void send_notification_to_all(server_t *server, char *msg);

void send_notification_to_all_except(server_t *server, char *msg,
    int ex_socket);

void send_user_logged_in_event(server_t *server, int client_socket);

void send_user_logged_out_event(server_t *server, int client_socket);

bool is_user_subscribed_to_team(team_t *team, char *client_uuid);

#endif /* !SERVER_H_ */

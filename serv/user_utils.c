/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** user_utils
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "server.h"
#include "str_utils.h"
#include "socket_utils.h"

client_db_t *get_user_from_db(client_db_t **registered, char *user_name)
{
    for (int i = 0; registered[i] != NULL; i++) {
        if (strcmp(registered[i]->user_name, user_name) == 0)
            return registered[i];
    }
    return NULL;
}

client_t *get_client_by_uuid(server_t *server, char *uuid)
{
    for (int i = 0; i < server->nb_clients_connected; i++) {
        if (server->clients_connected[i].uuid != NULL &&
            strcmp(server->clients_connected[i].uuid, uuid) == 0)
            return &server->clients_connected[i];
    }
    return NULL;
}

void register_client_to_db(client_t client, server_db_t *db)
{
    int len = db_user_len(db->registered_clients);

    db->registered_clients = realloc(db->registered_clients, (len + 2) *
        sizeof(struct client_db_s *));

    db->registered_clients[len] = malloc(1 * sizeof(struct client_db_s));
    db->registered_clients[len]->user_name = malloc((strlen(client.user_name)
        + 1) * sizeof(char));
    db->registered_clients[len]->uuid = malloc((strlen(client.uuid) + 1) *
        sizeof(char));
    strcpy(db->registered_clients[len]->user_name, client.user_name);
    strcpy(db->registered_clients[len]->uuid, client.uuid);
    db->registered_clients[len + 1] = NULL;
    save_database(*db);
}

client_db_t *get_db_client_by_uuid(server_db_t database, char *uuid)
{
    for (int i = 0; database.registered_clients[i] != NULL; i++) {
        if (strcmp(database.registered_clients[i]->uuid, uuid) == 0)
            return database.registered_clients[i];
    }
    return NULL;
}

void send_418_to_client(int client_socket, char *uuid_not_found)
{
    char *dest = malloc(11 * sizeof(char));

    dest = strcpy(dest, "418 User ");
    dest = str_concat(dest, uuid_not_found);
    dest = str_concat(dest, " not found.");
    write_to_socket(client_socket, str_concat(dest, CRLF));
}

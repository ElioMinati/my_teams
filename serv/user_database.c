/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** user_database
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "str_utils.h"

int db_user_len(client_db_t **clients)
{
    int i = 0;

    for (; clients[i] != NULL; i++);
    return i;
}

void save_users(FILE *stream, client_db_t **users)
{
    fprintf(stream, "%s:%s", DB_USER_SECTION, DB_LINE_SEPARATOR);
    for (int i = 0; users[i] != NULL; i++) {
        fprintf(stream, "%s %s%s", users[i]->uuid, users[i]->user_name,
            DB_LINE_SEPARATOR);
    }
}

static client_db_t *parse_db_user(char *to_parse)
{
    client_db_t *cli = malloc(1 * sizeof(struct client_db_s));
    char **usr = my_str_to_word_array(to_parse, ' ');
    cli->uuid = malloc((strlen(usr[0]) + 1) * sizeof(char));
    cli->user_name = malloc((strlen(usr[1]) + 1) * sizeof(char));
    strcpy(cli->uuid, usr[0]);
    strcpy(cli->user_name, usr[1]);
    free_array(usr);
    return cli;
}

static client_db_t **user_append(client_db_t **registered, char *to_append)
{
    int len = db_user_len(registered);

    registered = realloc(registered, (len + 2) *
        sizeof(struct client_db_s *));
    registered[len] = parse_db_user(to_append);
    registered[len + 1] = NULL;
    return registered;
}

client_db_t **parse_users(char *raw_file)
{
    client_db_t **registered_users = malloc(1 * sizeof(struct client_db_s *));
    char **lines = NULL;
    bool at_section = false;
    registered_users[0] = NULL;
    if (raw_file == NULL)
        return registered_users;
    lines = my_str_to_word_array(raw_file, '\n');
    for (int i = 0; lines[i] != NULL; i++) {
        if (strcmp(lines[i], DB_TABLE_SEPARATOR) == 0) {
            at_section = false;
            continue;
        }
        registered_users = (at_section ?
            user_append(registered_users, lines[i]) : registered_users);
        if (strcmp(lines[i], str_concat(DB_USER_SECTION, ":")) == 0)
            at_section = true;
    }
    free_array(lines);
    return registered_users;
}

/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** server_database
*/

#include <stdio.h>
#include <stdlib.h>
#include "server.h"
#include "file_utils.h"
#include "str_utils.h"
#include "logging_server.h"

void save_database(server_db_t db)
{
    FILE *stream = NULL;

    remove(DB_PATH);
    stream = fopen(DB_PATH, "w");
    save_users(stream, db.registered_clients);
    fprintf(stream, "%s%s", DB_TABLE_SEPARATOR, DB_LINE_SEPARATOR);
    save_messages(stream, db.exchanged_messages);
    fprintf(stream, "%s%s", DB_TABLE_SEPARATOR, DB_LINE_SEPARATOR);
    save_teams(stream, db.teams);
    fprintf(stream, "%s%s", DB_TABLE_SEPARATOR, DB_LINE_SEPARATOR);
    save_channels(stream, db.teams);
    fprintf(stream, "%s%s", DB_TABLE_SEPARATOR, DB_LINE_SEPARATOR);
    save_threads(stream, db.teams);
    fprintf(stream, "%s%s", DB_TABLE_SEPARATOR, DB_LINE_SEPARATOR);
    save_replies(stream, db.teams);
    fprintf(stream, "%s%s", DB_TABLE_SEPARATOR, DB_LINE_SEPARATOR);
    fclose(stream);
}

server_db_t load_database(void)
{
    server_db_t db;
    char *raw_db = read_file(DB_PATH);

    db.registered_clients = parse_users(raw_db);
    db.exchanged_messages = parse_sent_messages(raw_db);
    db.teams = parse_teams(raw_db);
    for (int i = 0; db.registered_clients[i] != NULL; i++)
        server_event_user_loaded(db.registered_clients[i]->uuid,
            db.registered_clients[i]->user_name);
    free(raw_db);
    return db;
}

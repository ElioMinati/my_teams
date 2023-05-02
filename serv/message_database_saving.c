/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** message_database_saving
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "str_utils.h"

static int db_msg_len(message_t **messages)
{
    int i = 0;

    for (; messages[i] != NULL; i++);
    return i;
}

void save_messages(FILE *stream, message_t **exchanged_messages)
{
    fprintf(stream, "%s:%s", DB_MSG_SECTION, DB_LINE_SEPARATOR);
    for (int i = 0; exchanged_messages[i] != NULL; i++) {
        fprintf(stream, "%s %s %li \"%s\"\n",
        exchanged_messages[i]->sender_uuid,
        exchanged_messages[i]->reciever_uuid, exchanged_messages[i]->timestamp,
        exchanged_messages[i]->msg);
    }
}

static message_t *parse_db_msg(char *raw_line)
{
    message_t *message = malloc(sizeof(struct message_s));
    char **seperated = my_str_to_word_array(raw_line, ' ');
    char **msg_arr = my_str_to_word_array(raw_line, '"');

    if (arrlen(seperated) < 4 || count_chars(raw_line, '"') != 2) {
        printf("ERROR parsing messages\n");
        return NULL;
    }
    message->sender_uuid = malloc((strlen(seperated[0]) + 1) * sizeof(char));
    message->reciever_uuid = malloc((strlen(seperated[1]) + 1) * sizeof(char));
    message->timestamp = atol(seperated[2]);
    message->msg = malloc((strlen(msg_arr[1]) + 2) * sizeof(char));
    message->msg = strcpy(message->msg, msg_arr[1]);
    message->sender_uuid = strcpy(message->sender_uuid, seperated[0]);
    message->reciever_uuid = strcpy(message->reciever_uuid, seperated[1]);
    return message;
}

message_t **message_log_append(message_t **messages, char *raw_line)
{
    int len = db_msg_len(messages);

    messages = realloc(messages, (len + 2) *
        sizeof(struct message_s *));
    messages[len] = parse_db_msg(raw_line);
    messages[len + 1] = NULL;
    return messages;
}

message_t **parse_sent_messages(char *raw_file)
{
    message_t **message_logs = malloc(1 * sizeof(struct message_s *));
    char **lines = NULL;
    bool at_section = false;
    message_logs[0] = NULL;
    if (raw_file == NULL)
        return message_logs;
    lines = my_str_to_word_array(raw_file, '\n');
    for (int i = 0; lines[i] != NULL; i++) {
        if (strcmp(lines[i], DB_TABLE_SEPARATOR) == 0) {
            at_section = false;
            continue;
        }
        message_logs = (at_section ?
            message_log_append(message_logs, lines[i]) : message_logs);
        if (strcmp(lines[i], str_concat(DB_MSG_SECTION, ":")) == 0)
            at_section = true;
    }
    free_array(lines);
    return message_logs;
}

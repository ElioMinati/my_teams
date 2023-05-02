/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** teams_saving
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"
#include "str_utils.h"

void save_teams(FILE *stream, team_t **teams)
{
    char *raw_line = NULL;
    fprintf(stream, "%s:%s", DB_TEAMS_SECTION, DB_LINE_SEPARATOR);
    for (int i = 0; teams[i] != NULL; i++) {
        raw_line = malloc((strlen(teams[i]->uuid) + strlen(teams[i]->name) +
        strlen(teams[i]->creator_uuid) + strlen(teams[i]->description) +
        100) * sizeof(char));
        sprintf(raw_line, "\"%s\" \"%s\" \"%s\" \"%s\" \"", teams[i]->uuid,
            teams[i]->creator_uuid, teams[i]->name, teams[i]->description);
        for (int j = 0; teams[i]->subscribed_users_uuid[j] != NULL; j++) {
            raw_line = str_concat(raw_line,teams[i]->subscribed_users_uuid[j]);
            raw_line = str_concat(raw_line, ",");
        }
        raw_line = str_concat(raw_line, "\" \"");
        for (int j = 0; teams[i]->channels[j] != NULL; j++) {
            raw_line = str_concat(raw_line, teams[i]->channels[j]->uuid);
            raw_line = str_concat(raw_line, ",");
        }
        raw_line = str_concat(raw_line, "\"");
        fprintf(stream, "%s\n", raw_line);
    }
}

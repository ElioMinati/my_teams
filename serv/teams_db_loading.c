/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** teams_db_loading
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "str_utils.h"
#include "server.h"

team_t *parse_db_team(char *raw_line, char **lines)
{
    team_t *team = malloc(sizeof(*team));
    char **all_args = my_str_to_word_array(raw_line, '"');
    char **channel_uuids = NULL;

    team->uuid = all_args[1];
    team->creator_uuid = all_args[3];
    team->name = all_args[5];
    team->description = all_args[7];
    team->subscribed_users_uuid = my_str_to_word_array(all_args[9], ',');
    channel_uuids = my_str_to_word_array(all_args[11], ',');
    if (count_chars(all_args[9], ',') == 0) {
        team->subscribed_users_uuid = malloc(1 * sizeof(char *));
        team->subscribed_users_uuid[0] = NULL;
    }
    team->channels = parse_channels(lines, channel_uuids);
    team->subscribed_users_uuid[count_chars(all_args[9], ',')] = NULL;
    return team;
}

team_t **team_append(team_t **teams, char *raw_line, char **lines)
{
    int len = get_teams_length(teams);

    teams = realloc(teams, (len + 2) *
        sizeof(struct team_t *));
    teams[len] = parse_db_team(raw_line, lines);
    teams[len + 1] = NULL;
    return teams;
}

team_t **parse_teams(char *raw_file)
{
    team_t **teams = malloc(1 * sizeof(struct team_s *));
    char **lines = NULL;
    bool at_section = false;

    teams[0] = NULL;
    if (raw_file == NULL)
        return teams;
    lines = my_str_to_word_array(raw_file, '\n');
    for (int i = 0; lines[i] != NULL; i++) {
        if (strcmp(lines[i], DB_TABLE_SEPARATOR) == 0) {
            at_section = false;
            continue;
        }
        teams = (at_section ?
            team_append(teams, lines[i], lines) : teams);
        if (strcmp(lines[i], str_concat(DB_TEAMS_SECTION, ":")) == 0)
            at_section = true;
    }
    free_array(lines);
    return teams;
}

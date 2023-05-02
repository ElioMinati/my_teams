/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** channel_utils
*/

#include <string.h>
#include "server.h"

int get_channels_length(channel_t **channels)
{
    int i = 0;

    for (; channels[i] != NULL; i++);
    return i;
}

bool channel_with_same_name_exists(channel_t **channels, char *name)
{
    for (int i = 0; channels[i] != NULL; i++) {
        if (strcmp(channels[i]->name, name) == 0)
            return true;
    }
    return false;
}

channel_t *get_channel_from_team(team_t *team, char *channel_uuid)
{
    if (team == NULL || channel_uuid == NULL)
        return NULL;
    for (int i = 0; team->channels[i] != NULL; i++) {
        if (strcmp(team->channels[i]->uuid, channel_uuid) == 0)
            return team->channels[i];
    }
    return NULL;
}

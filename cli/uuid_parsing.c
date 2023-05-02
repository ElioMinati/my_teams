/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** uuid_parsing
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "client.h"

char *parse_uuid_from_server_response(char *response)
{
    char *beg = strchr(response, '\"') + 1;
    char *dest = malloc((UUID_LEN + 1) * sizeof(char));

    dest = strncpy(dest, beg, UUID_LEN);
    dest[UUID_LEN] = '\0';
    return dest;
}

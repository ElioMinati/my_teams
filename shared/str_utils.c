/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** str_utils
*/

#include <stdlib.h>
#include <string.h>

char *str_realloc(char *src)
{
    char *dest = malloc((strlen(src) + 2) * sizeof(char));

    dest = strcpy(dest, src);
    dest[strlen(src)] = '\0';
    free(src);
    return dest;
}

char *str_concat(char *src, char *str)
{
    char *dest = malloc((strlen(src) + strlen(str) + 2) * sizeof(char));

    dest = strcpy(dest, src);
    dest = strcat(dest, str);
    return dest;
}

/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** file_utils
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "str_utils.h"

char *read_file(const char *filepath)
{
    size_t len = 1;
    int tmp_len = 0;
    char *dest = malloc(1 * sizeof(char));
    int c;
    FILE *file_ptr = fopen(filepath, "r");

    dest[0] = '\0';
    if (file_ptr == NULL) {
        return NULL;
    }
    while ((c = fgetc(file_ptr)) != EOF) {
        len++;
        dest = str_realloc(dest);
        tmp_len = strlen(dest);
        dest[tmp_len] = c;
        dest[tmp_len + 1] = '\0';
    }
    fclose(file_ptr);
    return dest;
}

/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** array_utils
*/

#include <stdlib.h>
#include <string.h>

int arrlen(char **array)
{
    int i = 0;

    for (; array[i] != NULL; i++);
    return i;
}

void free_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++) {
        free(array[i]);
    }
    free(array);
}

char **array_append(char **array, char *to_add)
{
    int len = arrlen(array);

    array = realloc(array, (len + 2) * sizeof(char *));
    array[len] = malloc((strlen(to_add) + 1) * sizeof(char));
    array[len] = strcpy(array[len], to_add);
    array[len + 1] = NULL;
    return array;
}

void array_remove(char **array, char *to_remove)
{
    int current_index = 0;

    for (int i = 0; array[i] != NULL; i++) {
        if (strcmp(array[i], to_remove) == 0) {
            free(array[i]);
            continue;
        }
        array[current_index] = array[i];
        current_index++;
    }
    array[current_index] = NULL;
}

char *array_find(char **array, char *to_cmp)
{
    for (int i = 0; array[i] != NULL; i++) {
        if (strcmp(array[i], to_cmp) == 0)
            return array[i];
    }
    return NULL;
}

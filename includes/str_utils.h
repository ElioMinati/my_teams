/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** str_utils
*/

#ifndef STR_UTILS_H_
    #define STR_UTILS_H_

char *str_realloc(char *);

char *str_concat(char *, char *);

char **my_str_to_word_array(char *str, char delimiter);

void free_array(char **array);

char *generate_new_uuid(int type);

char *parse_uuid_from_server_response(char *response);

int count_chars(char *str, char c);

int arrlen(char **);

char **array_append(char **array, char *to_add);

char *array_find(char **array, char *to_cmp);

void array_remove(char **array, char *to_remove);

#endif /* !STR_UTILS_H_ */

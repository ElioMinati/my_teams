/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** protocol
*/

#ifndef PROTOCOL_H_
    #define PROTOCOL_H_
    // 4xx: Errors
    #define MSG_402 "402 Invalid number of arguments."
    #define MSG_403 "403 Not authorized."
    #define MSG_404 "404 Unknown command."
    #define MSG_405 "405 Syntax error in parameters or arguments."
    #define MSG_412 "412 Already logged in."
    #define MSG_413 "413 Already Exists."
    #define MSG_415 "415 '\"' or ',' characters cannot be present in name."
    // 2xx: Connection
    #define MSG_201 "201 Service ready for new user."
    #define MSG_205 "205 User created successfully."
    #define MSG_207 "207 User logged in succesfully."
    #define MSG_214 "214 Help message."
    #define MSG_299 "299 Goodbye."
    // 3xx: Misc
    #define MSG_300 "300 Command okay."

#endif /* !PROTOCOL_H_ */

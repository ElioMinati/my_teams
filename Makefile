##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

CLI_SRC	=	cli/main_cli.c	\
			cli/error_handling.c	\
			cli/init_client.c	\
			cli/command_sending.c	\
			cli/info_recieving.c	\
			cli/select_parsing.c	\
			cli/uuid_parsing.c	\
			cli/send_info_parsing.c	\
			cli/user_parsing.c	\
			cli/error_parsing.c	\
			cli/message_recieve.c	\
			cli/creation_parsing.c	\
			cli/create_recieving.c	\
			cli/team_parsing.c	\
			cli/list_recieving.c	\
			cli/logging_events.c

SERV_SRC	=	serv/main_serv.c	\
				serv/error_handling.c	\
				serv/client_utils.c	\
				serv/client_command_parsing.c	\
				serv/init_server.c	\
				serv/select_parsing.c	\
				serv/server_database.c	\
				serv/uuid_utils.c	\
				serv/user_utils.c	\
				serv/user_logging.c	\
				serv/user_database.c	\
				serv/user_logout.c	\
				serv/user_connection_utils.c	\
				serv/user_listing.c	\
				serv/message_database_saving.c	\
				serv/message_commands.c	\
				serv/message_utils.c	\
				serv/context_setting.c	\
				serv/create_context.c	\
				serv/team_creation.c	\
				serv/teams_db_loading.c	\
				serv/teams_saving.c	\
				serv/team_utils.c	\
				serv/team_subscribing.c	\
				serv/channel_creation.c	\
				serv/channel_db_saving.c	\
				serv/channel_utils.c	\
				serv/thread_db_saving.c	\
				serv/thread_utils.c	\
				serv/thread_loading.c	\
				serv/thread_creation.c	\
				serv/reply_db_saving.c	\
				serv/reply_utils.c	\
				serv/reply_loading.c	\
				serv/reply_creation.c	\
				serv/list_command.c	\
				serv/list_utils.c	\
				serv/info_sending.c	\
				serv/notification_utils.c	\
				serv/logging_events.c	\
				serv/subscribed_sending.c

SHARED_SRC	= 	shared/port_utils.c	\
				shared/fd_utils.c	\
				shared/str_utils.c	\
				shared/array_utils.c	\
				shared/my_str_to_word_array.c	\
				shared/file_utils.c	\
				shared/write_utils.c

NAME_CLI	=	myteams_cli	\

NAME_SERV	=	myteams_server	\

CFLAGS	=	-Iincludes/ -Ilibs/myteams/ -g	\

LDFLAGS =	-L./libs/myteams -l${LOG_LIB_NAME}

CC	=	gcc	\

OBJ_CLI	=	$(CLI_SRC:.c=.o)

OBJ_SERV	=	$(SERV_SRC:.c=.o)

SHARED_OBJ	=	$(SHARED_SRC:.c=.o)

LOG_LIB_NAME = myteams

all:	 $(SHARED_OBJ) serv cli

cli:	$(NAME_CLI)

serv:	$(NAME_SERV)

$(NAME_CLI): $(OBJ_CLI)
	$(CC) -o $(NAME_CLI) $(LDFLAGS) $(OBJ_CLI) $(SHARED_OBJ)
	@echo -e "\x1b[32mClient compilation Success\e[0m"

$(NAME_SERV): $(OBJ_SERV)
	$(CC) -o $(NAME_SERV) $(LDFLAGS) $(OBJ_SERV) $(SHARED_OBJ)
	@echo -e "\x1b[32mServer compilation Success\e[0m"

clean:
	@$(RM) $(OBJ_CLI)
	@$(RM) $(OBJ_SERV)
	@$(RM) $(SHARED_OBJ)
	@echo -e "\x1b[32mClean Success\e[0m"

fclean: clean
	@$(RM) $(NAME_SERV)
	@$(RM) $(NAME_CLI)
	@$(RM) lib${LOG_LIB_NAME}.so
	@echo -e "\x1b[32mFclean Success\e[0m"

re:	fclean all

.PHONY: all serv cli clean fclean re

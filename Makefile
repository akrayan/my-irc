##
## Makefile for Makefile in /home/rayan/Memory/PSU_2016_nmobjdump
## 
## Made by Rayan
## Login   <raihane.akkache@epitech.net>
## 
## Started on  Sun Feb 26 11:30:35 2017 Rayan
## Last update Sun Jun 11 20:46:36 2017 TheNasCrazy
##

RM		=	rm -f

SERVER		=	server

CLIENT		=	client

SRC_S		= 	server_d/serv.c \
			server_d/main.c \
			server_d/ft_cmd.c \
			server_d/ft_cmd_bis2.c \
			server_d/ft_cmd_bis.c \
			server_d/add.c \
			server_d/init.c \
			server_d/tab.c \
			str.c

SRC_C		=	client_d/client.c \
			client_d/tab.c \
			client_d/get_next_line.c \
			str.c

CFLAGS		=  #-W -Wall -Werror -Wextra

OBJS_S		= $(SRC_S:.c=.o)

OBJS_C		= $(SRC_C:.c=.o)

all:		$(SERVER) $(CLIENT)

$(SERVER):	$(OBJS_S)
		gcc -o $(SERVER) $(OBJS_S)

$(CLIENT):	$(OBJS_C)
		gcc -o $(CLIENT) $(OBJS_C)

clean:
		$(RM) $(OBJS_S) $(OBJS_C)

fclean: 	clean
		$(RM) $(SERVER) $(CLIENT)

re:		fclean all

.PHONY:		all clean fclean re

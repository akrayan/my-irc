/*
** irc.h for irc.h in /home/rayan/System_Unix/Reseau/PSU_2016_myirc
**
** Made by Rayan
** Login   <raihane.akkache@epitech.eu>
**
** Started on  Thu Jun  1 14:04:16 2017 Rayan
** Last update Sun Jun 11 16:47:44 2017 Rayan
*/

#ifndef	IRC_H_
# define IRC_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

typedef struct			s_client
{
  int				fd;
  char				*nick;
  char				*ip;
  char				**chanel;
  struct s_client		*next;
  struct s_client		*last;
}				client;

typedef struct			s_serv
{
  int				fd;
  struct protoent		*pe;
  struct sockaddr_in		s_in;
  struct sockaddr_in		s_in_cl;
  socklen_t			s_in_size;
  int				port;
  fd_set			readfds;
  fd_set			writefds;
  fd_set			excpfds;
  client			*cl_list;
  char				**chanel;
}				serv;

client		*sup_client(client *cl_list, client *cl);
int		word_len(char *s, char c, int i);
int		nb_word(char *s, char c);
int		len_for_epure(char *s, char c);
char		*epure_str(char *s, char c);
char		**str_to_wordtab(char *s, char c);
int		cmd_users(client *cl, serv *serv, char **arg, char *buff);
int		cmd_quit(client *cl, serv *serv, char **arg, char *buff);
int		cmd_names(client *cl, serv *serv, char **arg, char *buff);
int		cmd_accept(client *cl, serv *serv, char **arg, char *buff);
int		cmd_msg(client *cl, serv *serv, char **arg, char *buff);
int		cmd_unknow(client *cl, serv *serv, char **arg, char *buff);
int		cmd_server(client *cl, serv *serv, char **arg, char *buff);
int		cmd_nick(client *cl, serv *serv, char **arg, char *buff);
int		cmd_list(client *cl, serv *serv, char **arg, char *buff);
int		cmd_join(client *cl, serv *serv, char **arg, char *buff);
int		cmd_part(client *cl, serv *serv, char **arg, char *buff);
int		is_in_tab(char **t, char *s);
int		tab_len(char **t);
char		**sup_chanel(char **t, char *to_del);
char		**add_chanel(char **t, char *new);
client		*add_client(client *cl_list, int fd, char *ip);
int		biggest_fd(client *cl_list, int fd);
int		id_cmd(char **arg);
int		check_cmd(client *cl, serv *server, char *s);
int		init_serv(char **av, serv *serv);
int		init_select(serv *serv);
int		check_select(serv *serv);
int		main(int ac, char **av);

#endif /* IRC_H_ */

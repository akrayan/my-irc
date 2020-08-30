/*
** add.c for add.c in /home/thenascrazy/tek2/Systeme_Unix/projet/PSU_2016_myirc/server_d
**
** Made by TheNasCrazy
** Login   <nacerdine.afou@epitech.eu>
**
** Started on  Sat Jun 10 19:06:23 2017 TheNasCrazy
** Last update Sun Jun 11 20:17:59 2017 Rayan
*/

#include "../include/irc.h"

int				cmd_quit(client *cl, serv *serv, char **arg, char *buff)
{
  close (cl->fd);
  serv->cl_list = sup_client(serv->cl_list, cl);
}

char				**sup_chanel(char **t, char *to_del)
{
  int				j;
  char				**chanel;

  j = -1;
  while (t[++j] != NULL);
  chanel = malloc(sizeof(char *) * j);
  j = -1;
  while (t[++j] != NULL && strcmp(t[j], to_del))
    chanel[j] = strdup(t[j]);
  while (t[j] != NULL && t[++j] != NULL)
    chanel[j - 1] = strdup(t[j]);
  chanel[j - 1] = NULL;
  j = -1;
  while (t[++j] != NULL)
    free(t[j]);
  free(t);
  return (chanel);
}

char				**add_chanel(char **t, char *new)
{
  int				j;
  char				**chanel;

  j = -1;
  while (t[++j] != NULL);
  chanel = malloc(sizeof(char *) * (j + 2));
  j = -1;
  while (t[++j] != NULL)
    chanel[j] = strdup(t[j]);
  chanel[j] = strdup(new);
  chanel[++j] = NULL;
  j = -1;
  while (t[++j] != NULL)
    free(t[j]);
  free(t);
  return (chanel);
}

client				*add_client(client *cl_list, int fd, char *ip)
{
  client			*new;

  new = malloc(sizeof(client));
  new->fd = fd;
  new->ip = ip;
  new->nick = strdup("Anonymous");
  new->chanel = malloc(sizeof(char *));
  new->chanel[0] = NULL;
  new->chanel = add_chanel(new->chanel, "default");
  new->last = new;
  new->next = NULL;
  if (cl_list == NULL)
    return (new);
  cl_list->last->next = new;
  cl_list->last = new;
  return (cl_list);
}

client				*sup_client(client *cl_list, client *cl)
{
  client			*p;

  p = cl_list;
  if (cl_list == cl)
    cl_list = cl_list->next;
  else
    {
      while (p != NULL && p->next != cl)
	p = p->next;
      p->next = cl->next;
    }
  return (cl_list);
}

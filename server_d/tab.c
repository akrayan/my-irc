/*
** tab.c for tab.c in /home/thenascrazy/tek2/Systeme_Unix/projet/PSU_2016_myirc/server_d
**
** Made by TheNasCrazy
** Login   <nacerdine.afou@epitech.eu>
**
** Started on  Sat Jun 10 19:04:30 2017 TheNasCrazy
** Last update Sat Jun 10 19:04:44 2017 TheNasCrazy
*/

#include "../include/irc.h"

int				is_in_tab(char **t, char *s)
{
  int				j;

  j = -1;
  while (t[++j] != NULL)
    if (strcmp(t[j], s) == 0)
      return (1);
  return (0);
}

int				tab_len(char **t)
{
  int				j;

  j = -1;
  while (t[++j] != NULL);
  return (j);
}

/*
** tab.c for tab.c in /home/thenascrazy/tek2/Systeme_Unix/projet/PSU_2016_myirc
**
** Made by TheNasCrazy
** Login   <nacerdine.afou@epitech.eu>
**
** Started on  Sun Jun 11 16:50:58 2017 TheNasCrazy
** Last update Sun Jun 11 16:54:25 2017 TheNasCrazy
*/

#include "../include/client.h"

int				tab_len(char **t)
{
  int				j;

  j = -1;
  while (t[++j] != NULL);
  return (j);
}

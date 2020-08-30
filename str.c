/*
** str.c for str.c in /home/rayan/System_Unix/Reseau/PSU_2016_myirc
** 
** Made by Rayan
** Login   <raihane.akkache@epitech.eu>
** 
** Started on  Tue Jun  6 18:43:33 2017 Rayan
** Last update Sun Jun 11 05:11:39 2017 Rayan
*/

#include "./include/irc.h"

int				word_len(char *s, char c, int i)
{
  int				nb;

  nb = 0;
  while (s[i] != '\0' && s[i] != c)
    {
      i++;
      nb++;
    }
  return (nb);
}

int				nb_word(char *s, char c)
{
  int				i;
  int				nb;

  i = -1;
  nb = 1;
  while (s[++i])
    {
      if (s[i] == c)
	nb++;
    }
  return (nb);
}

int				len_for_epure(char *s, char c)
{
  int				i;
  int				j;
  char				*r;

  j = 0;
  i = -1;
  while (s[++i] == c);
  while (s[i] != '\0')
    {
      j++;
      if (s[i] == c)
	{
	  while (s[++i] == c);
	  if (s[i] == '\0')
	    j--;
	}
      else
	i++;
    }
  return (j);
}

char				*epure_str(char *s, char c)
{
  int				i;
  int				j;
  char				*r;

  r = malloc(len_for_epure(s, c) + 1);
  j = 0;
  i = -1;
  while (s[++i] == c);
  while (s[i] && s[i] != '\n')
    {
      r[j] = s[i];
      j++;
      if (s[i] == c)
	{
	  while (s[++i] == c);
	  if (!s[i] || s[i] == '\n')
	    j--;
	}
      else
	i++;
    }
  r[j] = '\0';
  return (r);
}

char				**str_to_wordtab(char *s, char c)
{
  int				i;
  int				j;
  int				k;
  char				**t;

  s = epure_str(s, c);
  t = malloc(sizeof(char *) * (nb_word(s, c) + 1));
  j = -1;
  i = 0;
  while (++j < nb_word(s, c))
    {
      k = 0;
      t[j] = malloc(word_len(s, c, i) + 1);
      while (s[i] != '\0' && s[i] != c)
	{
	  t[j][k] = s[i];
	  i++;
	  k++;
	}
      t[j][k] = '\0';
      i++;
    }
  t[j] = NULL;
  return (t);
}

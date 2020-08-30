/*
** get_next_line.c for get_next_line.c in /home/thenascrazy/Téléchargements/lemin
**
** Made by TheNasCrazy
** Login   <nacerdine.afou@epitech.eu>
**
** Started on  Tue Apr 25 16:23:45 2017 TheNasCrazy
** Last update Sun Jun 11 21:28:26 2017 TheNasCrazy
*/

#include "../include/client.h"

int	check_end_line(char *buffer)
{
  int	i;

  i = 0;
  while (buffer[i] != '\0')
    {
      if (buffer[i] == '\n')
	return (i + 1);
      i = i + 1;
    }
  return (-1);
}

char		*my_two_str(char *result, char *buffer)
{
  int		i;
  int		j;
  char		*copy;

  i = -1;
  while (result[++i] != '\0');
  if ((copy = malloc(sizeof(char) * (i + READ_SIZE + 1))) == NULL)
    return (NULL);
  i = 0;
  while (result[i] != '\0')
    {
      copy[i] = result[i];
      i = i + 1;
    }
  j = 0;
  while (buffer[j] != '\0' && buffer[j] != '\n')
    {
      copy[i] = buffer[j];
      i = i + 1;
      j = j + 1;
    }
  copy[i] = '\0';
  free(result);
  return (copy);
}

int		rest_of_read(char *buffer, int *k, char **result)
{
  int		i;

  i = *k;
  while (buffer[i] != '\0' && buffer[i] != '\n')
    i = i + 1;
  if (((*result) = malloc(sizeof(char) * (i - *k + 1))) == NULL)
    return (-1);
  i = 0;
  while (buffer[*k] != '\0' && buffer[*k] != '\n')
    {
      (*result)[i] = buffer[*k];
      *k = *k + 1;
      i = i + 1;
    }
  (*result)[i] = '\0';
  if (buffer[*k] == '\n')
    {
      *k = *k + 1;
      return (1);
    }
  return (0);
}

char		*get_next_line(const int fd)
{
  static char	buffer[READ_SIZE + 1];
  static int	k = 0;
  char		*result;
  int		ret;

  ret = rest_of_read(buffer, &k, &result);
  if (ret == -1)
    return (NULL);
  else if (ret == 1)
    return (result);
  while ((ret = read(fd, buffer, READ_SIZE)) > 0)
    {
      buffer[ret] = '\0';
      result = my_two_str(result, buffer);
      if ((k = check_end_line(buffer)) != -1)
	return (result);
    }
  if (result[0] != '\0')
    return (result);
  free(result);
  return (NULL);
}

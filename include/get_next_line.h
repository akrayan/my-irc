/*
** get_next_line.h for get_next_line.h in /home/thenascrazy/Téléchargements/lemin
**
** Made by TheNasCrazy
** Login   <nacerdine.afou@epitech.eu>
**
** Started on  Tue Apr 25 16:22:59 2017 TheNasCrazy
** Last update Sun Jun 11 19:52:32 2017 TheNasCrazy
*/

#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

#ifndef READ_SIZE
# define READ_SIZE (4096)
#endif /* !READ_SIZE */

# include <stdlib.h>
# include <unistd.h>

int		check_end_line(char *buffer);
char		*my_two_str(char *result, char *buffer);
int		rest_of_read(char *buffer, int *k, char **result);
char		*get_next_line(const int fd);

#endif /* !GET_NEXT_LINE */

/*
** main.c for main.c in /home/thenascrazy/tek2/Systeme_Unix/bootstrap/reseaux
**
** Made by TheNasCrazy
** Login   <nacerdine.afou@epitech.eu>
**
** Started on  Thu Jun  8 14:50:27 2017 TheNasCrazy
** Last update Sun Jun 11 20:46:15 2017 TheNasCrazy
*/

#include "../include/client.h"

int	init_client(t_client *client)
{
  client->pe = getprotobyname("TCP");
  client->fd_server = socket(AF_INET, SOCK_STREAM, client->pe->p_proto);
  if (!client->pe)
    return (1);
  if (client->fd_server == -1)
    return (1);
  client->s_in.sin_family = AF_INET;
  client->s_in.sin_port = htons(client->port);
  client->s_in.sin_addr.s_addr = inet_addr(client->ip);
  if (connect(client->fd_server,
	      (struct sockaddr *)&client->s_in, sizeof(client->s_in)) == -1)
    {
      write(1, "J'arrive pas a me co\n", 22);
      if (close(client->fd_server) == -1)
	return (1);
      return (1);
    }
}

int	main_loop(t_client *client)
{
  int			ret;

  FD_ZERO(&client->readfds);
  FD_SET(client->fd_server, &client->readfds);
  FD_SET(0, &client->readfds);
  select(client->fd_server + 1, &client->readfds, NULL, NULL, NULL);
  if (FD_ISSET(0, &client->readfds))
    {
      client->s = get_next_line(0);
      dprintf(client->fd_server, "%s\n", client->s);
    }
  if (FD_ISSET(client->fd_server, &client->readfds))
    {
      if ((ret = read(client->fd_server, client->s_server, 4096)) > 0)
	{
	  client->s_server[ret] = '\0';
	  dprintf(1, "%s\n", client->s_server);
	}
    }
  return (0);
}

int	main(int ac, char **av)
{
  t_client		client;

  if (ac != 3)
    return (1);
  client.port = atoi(av[2]);
  client.ip = av[1];
  if (init_client(&client) == 1)
    return (1);
  while (42)
    main_loop(&client);
  if (close(client.fd_server) == -1)
    return (1);
  return (0);
}

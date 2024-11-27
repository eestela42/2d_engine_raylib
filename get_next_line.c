/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:37:40 by kle-rest          #+#    #+#             */
/*   Updated: 2022/12/11 18:07:46 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_next_gnl(char *stash)
{
	char	*next;
	int		i;
	int		j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	next = malloc(sizeof(char) * (ft_strlen_gnl(stash) - i + 1));
	if (!next)
		return (NULL);
	j = 0;
	while (stash[i])
		next[j++] = stash[i++];
	next[j] = '\0';
	free(stash);
	return (next);
}

char	*ft_line_gnl(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (stash[0] == '\0')
		return (NULL);
	line = ft_calloc_gnl(sizeof(char), (ft_strlen_gnl(stash) + 1));
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = stash[i];
		line[i + 1] = '\0';
	}
	else
		line[i] = '\0';
	return (line);
}

char	*ft_read_gnl(int fd, char *stash)
{
	char	*bufread;
	int		ret;

	ret = 1;
	bufread = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	while (ret != 0 && ft_checkline_gnl(stash) == 0)
	{
		ret = read(fd, bufread, BUFFER_SIZE);
		if (ret == -1)
		{
			free(bufread);
			return (NULL);
		}
		bufread[ret] = '\0';
		stash = ft_strjoin_gnl(stash, bufread);
	}
	free(bufread);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stash = ft_read_gnl(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_line_gnl(stash);
	stash = ft_next_gnl(stash);
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alflores <alflores@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:06:03 by alflores          #+#    #+#             */
/*   Updated: 2023/02/21 17:21:45 by alflores         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_buffer(char *buffer, int fd)
{
	char	*aux;
	int		i;

	if (buffer && ft_strchr (buffer, '\n'))
		return (buffer);
	aux = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!aux)
		return (NULL);
	i = 1;
	while (i != 0)
	{
		i = read(fd, aux, BUFFER_SIZE);
		if (i == -1)
		{
			free(buffer);
			free(aux);
			return (NULL);
		}
		aux[i] = '\0';
		buffer = ft_strjoin(buffer, aux);
		if (ft_strchr (buffer, '\n'))
			break ;
	}
	free(aux);
	return (buffer);
}

char	*get_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	line = ft_calloc(sizeof(char), (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n' && buffer[i])
		line[i] = buffer[i];
	return (line);
}

char	*get_clean_buffer(char *buffer)
{
	char	*extra;
	int		l_line;
	int		l_extra;

	l_line = 0;
	l_extra = 0;
	while (buffer[l_line] != '\n' && buffer[l_line] != '\0')
		l_line++;
	if (!buffer[l_line])
	{
		free (buffer);
		return (NULL);
	}
	l_line++;
	extra = ft_calloc(sizeof(char), (ft_strlen(buffer) - l_line + 1));
	if (!extra)
	{
		free (buffer);
		return (NULL);
	}
	while (buffer[l_line])
		extra[l_extra++] = buffer[l_line++];
	extra[l_extra] = '\0';
	free (buffer);
	return (extra);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_calloc(sizeof(char), 1);
	buffer[fd] = get_buffer(buffer[fd], fd);
	if (!buffer[fd])
		return (0);
	line = get_line(buffer[fd]);
	buffer[fd] = get_clean_buffer(buffer[fd]);
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alflores <alflores@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:06:03 by alflores          #+#    #+#             */
/*   Updated: 2023/02/02 20:42:07 by alflores         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_buffer(char *buffer, int fd)
{
	char	*aux;
	char	*aux_buffer;
	int		i;
	
	if(!buffer)
		buffer = ft_calloc(sizeof(char), 1);
	aux	 = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if(!aux)
		return (NULL);
	i = 1;
	while (!ft_strchr(aux, '\n') && i != 0)
	{
		aux_buffer = buffer;
		i = read(fd, aux, BUFFER_SIZE);
		if (i == -1)
		{
			free(aux);
			free(buffer);
			return (NULL);
		}
		free (buffer);
		aux[i] = '\0';
		buffer = ft_strjoin(aux_buffer, aux);
	}
	free (aux);
	return (buffer);
}

char	*get_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer)
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
	if (buffer[i] == '\n')
		line[i] = buffer[i];
/* 	printf("%s\n", line); */
	return (line);
}

char	*get_clean_buffer(char *buffer)
{
	char	*extra;
	int		l_line;
	int		l_trash;
	
	l_line = 0;
	while (buffer[l_line] != '\n' && buffer[l_line] != '\0')
		l_line++;
	l_line++;
	extra = ft_calloc(sizeof(char), (ft_strlen(buffer) - l_line));
	if (!extra)
		return (NULL);
	l_trash = 0;
	while (buffer[l_line] != '\0')
	{
		extra[l_trash++] = buffer[l_line++];
	}
	return (extra); 
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = get_buffer(buffer[fd], fd);
	if (!buffer[fd])
		return (NULL);
	line = get_line(buffer[fd]);
	buffer[fd] = get_clean_buffer(buffer[fd]);
	return (line);
}

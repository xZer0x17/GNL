/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alflores <alflores@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:44:54 by alflores          #+#    #+#             */
/*   Updated: 2023/02/02 20:13:23 by alflores         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	line = ft_calloc(sizeof(char), (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
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
	char	*trash;
	int		l_line;
	int		l_trash;
	
	l_line = 0;
	while (buffer[l_line] != '\n' && buffer[l_line] != '\0')
		l_line++;
	if (!buffer[l_line])
	{
		free (buffer);
		return (NULL);
	}
	l_line++;
	trash = malloc(sizeof(char) * (ft_strlen(buffer) - l_line));
	if (!trash)
		return (NULL);
	l_trash = 0;
	while (buffer[l_line])
		trash[l_trash++] = buffer[l_line++];
	free (buffer);
	return (trash); 
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = get_buffer(buffer, fd);
	if (!buffer)
		return (NULL);
	line = get_line(buffer);
	buffer = get_clean_buffer(buffer);
	return (line);
}

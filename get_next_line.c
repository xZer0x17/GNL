/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alflores <alflores@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:44:54 by alflores          #+#    #+#             */
/*   Updated: 2023/02/02 19:18:45 by alflores         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_bbc(char *bbc, int fd)
{
	char	*buffer;
	int		i;
	char	*aux;
	
	if(!bbc)
		bbc = calloc(sizeof(char), 1);
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if(!buffer)
		return (NULL);
	i = 1;
	while (i != 0)
	{
		aux = bbc;
		i = read(fd, buffer, BUFFER_SIZE);
		free (bbc);
		bbc = ft_strjoin(aux, buffer);
	}
	return (bbc);
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
	return (line);
}

char	*get_chupadita_bbc(char *bbc)
{
	char	*trash;
	int		l_line;
	int		l_trash;
	
	l_line = 0;
	while (bbc[l_line] != '\n' && bbc[l_line] != '\0')
		l_line++;
	l_line++;
	trash = ft_calloc(sizeof(char), (ft_strlen(bbc) - l_line));
	if (!trash)
		return (NULL);
	l_trash = 0;
	while (bbc[l_line] != '\0')
	{
		trash[l_trash++] = bbc[l_line++];
	}
	return (trash); 
}

char	*get_next_line(int fd)
{
	static char	*bbc;
	char		*line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bbc = get_bbc(bbc, fd);
	if (!bbc)
		return (NULL);
	line = get_line(bbc);
	bbc = get_chupadita_bbc(bbc);
	return (line);
}

/* int main()
{
	char	*aux;
	int		fd= open("prueba1.txt", O_RDONLY);
	
	for(int i = 1; i <= 5; i++)
	{
		printf("1\n");
		aux = get_next_line(fd);
		printf("%s\n",aux);
		free(aux);
	}
}
 */
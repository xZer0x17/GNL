/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alflores <alflores@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:06:03 by alflores          #+#    #+#             */
/*   Updated: 2023/02/02 19:13:57 by alflores         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_buffer(char *buffer, int fd)//Esta funcion es la que va a tener todo lo leido, más lo de antes si esk sobra algo
{
	char	*aux;
	int		i;
	
	if(!buffer)
		buffer = ft_calloc(sizeof(char), 1);//No le pongo null, pork quiero que este vacio no que no exista
	aux	 = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if(!aux)
		return (NULL);
	i = 1;
	while (i != 0)//va a entrar una vez
	{
		i = read(fd, aux, BUFFER_SIZE);
		aux[i] = '\0';
		buffer = ft_strjoin(buffer, aux);
	}
	return (buffer);
}

char	*get_line(char *buffer)//Aquí saca la línea de la estatica
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;//Con esto tengo el tamaño de lo que voy a llenar
	line = ft_calloc(sizeof(char), (i + 2));//+2 por si es un \n y como uso calloc todo son 0 asique me da igual
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')//Con esto lo ire  sustituyendo
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i] = buffer[i];
/* 	printf("%s\n", line); */
	return (line);
}

char	*get_clean_buffer(char *buffer)//Consigo lo que sobra de la función
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
	static char	*buffer[3072];
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

/* int main()
{
	char	*aux;
	char	*aux2;
	int		fd= open("prueba1.txt", O_RDONLY);
	int		fc= open("prueba.txt", O_RDONLY);
	for(int i = 1; i <= 5; i++)
	{
		aux = get_next_line(fd);
		aux2 = get_next_line(fc);
		printf("%s\n",aux2);
		printf("%s\n",aux);
		free(aux);
		free(aux2);
	}
} */

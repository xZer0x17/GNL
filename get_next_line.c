/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alflores <alflores@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:20:57 by alflores          #+#    #+#             */
/*   Updated: 2023/01/29 17:09:23 by alflores         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(char *buffer)//Sacar hasta el primer salto de línea o final del txt
{
	int		i;
	char	*aux;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')//Recorre el buffer buscando el salto de línea
		i++;
	if (buffer[i] == '\n')//¿tener en cuenta que salto de línea es un caracter más?
		i++;
	aux = (char *)malloc(sizeof(char) * i + 1);//Va a tener el tamañano de la línea
	if (!aux)//Gestión de error
		return (0);
	ft_strlcpy(aux, buffer, i + 1);//Vamos pegando en el espacio reservado la línea
	return (aux);
}

char	*ft_trash(char *bbc, char *line) //Junta la mierda restante y hasta el salto de linea del read
{
	char	*aux;
	int		i;
	int		l_trash;

	i = -1;
	l_trash = ft_strlen(bbc) - ft_strlen(line)*2;
	aux = (char *)malloc(sizeof(char) * l_trash + 1);
	if (ft_strlen(line) > ft_strlen(bbc))
		return (ft_strjoin(bbc, line));
	while (++i < l_trash)
		aux[i] = bbc[i];
	return (aux);
}

char	*get_next_line(int fd)//Función que leerá un txt en función al B_S pero que irá imprimiendo todas las líneas del txt
{
	static char	*bbc;
	char		*line;
	char		*buffer;
	int			l_len;

	if (BUFFER_SIZE < 1 || fd < 0)//Gestión de error
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);//Reservamos memoria, porque si fuera un string de espacio indefinido, da error de segmention fault
	read(fd, buffer, BUFFER_SIZE);//Vamos llenando lo que leemos en el buffer
	if (bbc == 0)//Para que suceda la primera vez que lee el archivo
	{
		line = get_line(buffer);//Saca la línea
		bbc = ft_substr(buffer, ft_strlen(line), ft_strlen(buffer));//Sacamos lo que haya sobrado de la primera leida
		/* printf("%s\n", bbc); */
		return(line);
	}
	line = get_line(buffer);//Buscando la línea en cualquier otra llamada de la función
	if (!line)//Gestión de errores
		return (0);
	l_len = ft_strlen(line);
	line = ft_trash(bbc, line);//Aquí va a entrar lo que ha sobrado de la primera leida más, de lo que haya leido, hasta el primer \n
	free (bbc);
	bbc = ft_substr(buffer, l_len, ft_strlen(buffer));
	//printf("%s\n", bbc);
	return (line);	

	return(line);	
}

int main()
{
	char *aux;
	int	fd=open("prueba1.txt", O_RDONLY);
/* 	int a = read(fd,aux,BUFFER_SIZE);
	printf("|%s|\n", aux); */
	for (int i = 1; i <= 3; i++){
		aux = get_next_line(fd);
		printf("%s\n",aux);
		free(aux);
	}
}
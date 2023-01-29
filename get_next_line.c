/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alflores <alflores@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:44:54 by alflores          #+#    #+#             */
/*   Updated: 2023/01/29 21:06:34 by alflores         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"








size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_bzero(void *str, size_t n)
{
	unsigned char	*aux;

	aux = str;
	if (n == 0)
		return ;
	while (n > 0)
	{
		*aux = '\0';
		aux++;
		n--;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	if (count == SIZE_MAX || size == SIZE_MAX)
		return (0);
	result = malloc(count * size);
	if (!result)
		return (0);
	ft_bzero(result, (count * size));
	return (result);
}

char	*ft_strdup(const char *src)
{
	char	*aux;
	int		i;

	i = 0;
	aux = (char *)malloc(ft_strlen(src) + 1);
	if (!aux)
		return (0);
	while (src[i] != '\0')
	{
		aux[i] = src[i];
		i++;
	}
	aux[i] = '\0';
	return (aux);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		a;
	int		b;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	a = ft_strlen(s1);
	b = ft_strlen(s2);
	i = 0;
	str = malloc(a + b + 1);
	if (!(str))
		return (NULL);
	while (a--)
	{
		str[i] = s1[i];
		i++;
	}
	a = i;
	i = 0;
	while (b--)
		str[a++] = s2[i++];
	str[a] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*aux;
	size_t			i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	if (len <= (size_t)ft_strlen(s))
		aux = (char *)malloc(sizeof(char) * (len + 1));
	else
		aux = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!aux)
		return (0);
	while (s[j] != '\0' && i < len)
	{
		if (j >= start)
			aux[i++] = s[j];
		j++;
	}
	aux[i] = '\0';
	return (aux);
}

int	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i < dstsize - 1 && src[i] && dstsize > 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}














char	*get_bbc(char *bbc, int fd)//Esta funcion es la que va a tener todo lo leido, más lo de antes si esk sobra algo
{
	char	*buffer;
	int		i;
	
	if(!bbc)
		bbc = calloc(sizeof(char), 1);//No le pongo null, pork quiero que este vacio no que no exista
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if(!buffer)
		return (NULL);
	i = 1;
	while (i != 0)//va a entrar siempre
	{
/* 		printf("2\n"); */
		i = read(fd, buffer, BUFFER_SIZE);
/* 		printf("%d\n", i);
		printf("%s\n", buffer); */
		buffer[i] = '\0';
		bbc = ft_strjoin(bbc, buffer);
/* 		printf("%s\n", bbc); */
	}
	return (bbc);
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

char	*get_chupadita_bbc(char *bbc)//Consigo lo que sobra de la función
{
	char	*trash;
	int		l_line;
	int		l_trash;
	
	l_line = 0;
	while (bbc[l_line] != '\n' && bbc[l_line] != '\0')
		l_line++;
	trash = ft_calloc(sizeof(char), (ft_strlen(bbc) - l_line + 1));
	l_line++;//Para el salto del línea :)))
	if (!trash)
		return (NULL);
	l_trash = 0;
	while (bbc[l_line] != '\0')
	{
		trash[l_trash++] = bbc[l_line++];
	}
	printf("%s\n", trash);
	printf("%s\n", bbc);
	return (trash); 
}
//TODO: bbc no avanza
char	*get_next_line(int fd)//Tengo que devolver línea a línea un txt
{
	static char	*bbc;
	char		*line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bbc = get_bbc(bbc, fd);
/* 	printf("%s\n", bbc); */
	if (!bbc)
		return (NULL);
	line = get_line(bbc);
	bbc = get_chupadita_bbc(bbc);
	return (line);
}

int main()
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
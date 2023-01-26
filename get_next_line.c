/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alflores <alflores@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:20:57 by alflores          #+#    #+#             */
/*   Updated: 2023/01/26 20:26:40 by alflores         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
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

char	*get_line(char *buf)
{
	int		i;
	int		len;
	char	*aux;

	i = -1;
	len = ft_strlen(buf);
	aux = (char *)malloc(sizeof(char) * len + 1);
	if (!aux)
		return(0);
	while (buf[++i] != '\n'){
		aux[i] = buf[i];
	}

	return (aux);
}

char	*get_next_line(int fd)
{
	static char	*bbc;
	char		*line;
	char		*buf;
	int			lineLen;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	read(fd, buf, BUFFER_SIZE);
	if (bbc == 0)
	{
		line = get_line(buf);
		bbc = ft_substr(buf, ft_strlen(line) + 1, ft_strlen(buf));
		printf("%s\n", bbc);
		return(line);
	}
	line = get_line(buf);
	if (!line)
		return (0);
	lineLen = ft_strlen(line);
	line = ft_strjoin(bbc, line);
	bbc = ft_substr(buf, lineLen, ft_strlen(buf));

	return(line);	
}

int main()
{
	char *aux;
	int	fd=open("prueba2.txt", O_RDONLY);
/* 	int a = read(fd,aux,BUFFER_SIZE);
	printf("|%s|\n", aux); */
	for (int i = 1; i <= 5; i++){
		aux = get_next_line(fd);
		printf("%s\n",aux);
		free(aux);
	}
}
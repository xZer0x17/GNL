/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alflores <alflores@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:20:57 by alflores          #+#    #+#             */
/*   Updated: 2023/01/25 21:05:53 by alflores         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

int	fd_read(int	fd)
{
	char	*bbc[9999]; //BIG BLACK CHAR
	int		i;
	static int nbytes = 0;
	
	printf("2\n");
	read (fd, &bbc, BUFFER_SIZE);
	
	printf("%d\n", nbytes);
	//printf("%s\n", bbc);
	while(bbc[i] != '\n')
		i++;
	if (nbytes != i)
	{
		printf("%c", bbc[i++]);
	}
	i++;
	nbytes = nbytes + i;
	printf("\n");

	return i;
}

int main()
{
	printf("4\n");
	int	fd = open("prueba.txt", O_RDONLY);
	printf("3\n");
	fd_read(fd);
}
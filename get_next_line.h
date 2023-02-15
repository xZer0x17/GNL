/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alflores <alflores@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:59:58 by alflores          #+#    #+#             */
/*   Updated: 2023/02/04 20:18:39 by alflores         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 17
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

void	ft_bzero(void *str, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(const char *str, int c);

char	*get_next_line(int fd);
char	*get_clean_buffer(char *buffer);
char	*get_line(char *buffer);
char	*get_buffer(char *buffer, int fd);

#endif

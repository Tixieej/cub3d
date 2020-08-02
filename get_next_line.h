/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/03 16:42:29 by rde-vrie      #+#    #+#                 */
/*   Updated: 2020/02/24 11:13:52 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 128

int		get_next_line(int fd, char **line);
void	shift_buffer(char *buffer, int n);
int		read_till_end(int fd, char **line, char *buffer, int *ret);
int		gnl_strlen(char *s);
char	*gnl_strcpy(char *join, char *s1, char *s2);
char	*gnl_strjoin(char *s1, char *s2, int n);
int		gnl_strchr(char *s, char c);

#endif

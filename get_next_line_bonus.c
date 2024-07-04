/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:05:58 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/07/03 14:06:00 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_line(int fd, char *current)
{
	ssize_t	read_check;
	char	*temp;
	char	*line;

	line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	read_check = 1;
	while (read_check > 0 && !ft_strchr(current, '\n'))
	{
		read_check = read(fd, line, BUFFER_SIZE);
		if (read_check == -1)
			return (free(current), NULL);
		line[read_check] = '\0';
		temp = current;
		current = ft_strjoin(current, line);
		free(temp);
	}
	free(line);
	return (current);
}

char	*get_line(char *str)
{
	size_t	i;
	char	*line;

	if (!str || !str[0])
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i++;
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*rest_of_line(char *line)
{
	char	*remainder;
	size_t	i;
	size_t	j;

	i = 0;
	if (!line || !(line + 1))
		return (NULL);
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (!line[i])
		return (free(line), NULL);
	remainder = ft_calloc(ft_strlen(line) - i, sizeof(char));
	i++;
	j = 0;
	while (line[i])
		remainder[j++] = line[i++];
	remainder[j] = '\0';
	free(line);
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*temp[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	temp[fd] = read_line(fd, temp[fd]);
	line = get_line(temp[fd]);
	temp[fd] = rest_of_line(temp[fd]);
	return (line);
}

// stores the original pointer 'current' in 'tmp' before modifying 'current'
// this ensures that u still have a reference 
// to the original memory block pointed to by 'current', 
// which you need to free after the new string is created

// read(fd, 0, 0) < 0 check whether that is a valid file descriptor 
// that can be read from

/* int main(void)
{
	char *line;
	char *line1;
	int fd = open("test.txt", O_RDONLY);
	int fd1 = open("test1.txt", O_RDONLY);
	printf("File Descriptor: %d\n", fd);
	printf("Buffer size: %d\n", BUFFER_SIZE);
	printf("File Descriptor: %d\n", fd1);
	for (int i = 0; i < 2; i++)
	{
		line = get_next_line(fd);
		line1 = get_next_line(fd1);
		printf("Read: %s\n", line);
		printf("Read: %s\n", line1);
		free(line1);
		free(line);
	}
	close(fd);
	return (0);
} */

// as we changed static char to an array we have to specify which index we
// are currently working on the easier thing to do is to set it to fd

// we want to sotre the left characters in the array at the index of the fd, 
// so if we have another fd, we won't be overwriting what was left from the
// other fd 

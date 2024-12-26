#include "test_exam.h"

char	*ft_strdup(char *src)
{
	char	*dest;
	int		i = 0;

	while (src[i])
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 2));
	if (!dest)
		return (NULL);
	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\n';
	i++;
	dest[i] = '\0';
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	buffer_pos;
	static int	buffer_read;
	char		line[700000];
	int			i = 0;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, BUFFER_SIZE);
			if (buffer_read <= 0)
				break ;
			buffer_pos = 0;
		}
		line[i++] = buffer[buffer_pos++];
		if (buffer[buffer_pos] == '\n')
		{
			buffer_pos++;
			break ;
		}
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}

int main(int argc, char **argv)
{
	char *line;

	if (argc != 2)
		return (1);
	int fd = open(argv[1], O_RDONLY);
	while ((line = get_next_line(fd)) != NULL) // check
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}

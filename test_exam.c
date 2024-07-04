#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	char	c;
	int		byte;
	char	*buffer;
	int 	i;

	i = 0;
	buffer = (char *)malloc(1000000);
	byte = read(fd, &c, 1);
	// ensure the initial read operation is performed 
	// the loop has a condition to check before it starts
	while (byte > 0 && c != '\n' && c != EOF)
	{
		buffer[i++] = c;
		byte = read(fd, &c, 1);
	}
	if (i == 0 || byte < 0)
		return (free(buffer), NULL);
	buffer[i] = '\0';
	return (buffer);

}

int main(void)
{
	int	fd;
	int	i;

	fd = open("test.txt", O_RDONLY);
	i = -1;
	while (++i < 5)
		printf("%s\n", get_next_line(fd));
	close (fd);
	return (0);
}
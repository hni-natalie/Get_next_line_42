char	*read_line(int fd, char *current)
{
	char	*line;
	char	*tmp;
	ssize_t	read_check;

	read_check = INT_MAX;
	line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (read_check > 0 && !ft_strchr(current, '\n'))
	{
		read_check = read(fd, line, BUFFER_SIZE);
		if (read_check == -1)
			return (free(line), NULL);
		line[read_check] = '\0';
  // tmp is used to tenporarily hold the current value of 'current'
  // prevent memory leak as if ft_strjoin allocates new memory for 'current'
  // the previous allocated memory can be freed 
		tmp = current;
		current = ft_strjoin(current, line);
		free(tmp);
	}
	free(line);
	return (current);
}

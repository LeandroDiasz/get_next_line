/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledias-d <ledias-d@student.42.rio>         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-04 17:50:09 by ledias-d          #+#    #+#             */
/*   Updated: 2024-11-04 17:50:09 by ledias-d         ###   ########.rio      */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*fill_line(int fd, char *backup, char *buffer)
{
	ssize_t	bytes;
	char	*temp;

	bytes = 1;
	while (bytes > 0)
	{
		if (!backup)
			backup = ft_strdup("");
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			free(backup);
			return (NULL);
		}
		buffer[bytes] = '\0';
		temp = backup;
		backup = ft_strjoin(backup, buffer);
		free(temp);
		if (ft_strchr(backup, '\n'))
			break ;
	}
	free(buffer);
	return (backup);
}

char	*set_line(char **backup)
{
	int		i;
	char	*line;
	char	*new_backup;

	i = 0;
	if (!(*backup)[i])
		return (NULL);
	while ((*backup)[i] != '\n' && (*backup)[i] != '\0')
		i++;
	line = ft_substr(*backup, 0, i + ((*backup)[i] == '\n'));
	if ((*backup)[i] == '\n')
		new_backup = ft_strdup(*backup + i + 1);
	else
		new_backup = NULL;
	free(*backup);
	*backup = new_backup;
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*backup[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	backup[fd] = fill_line(fd, backup[fd], buffer);
	if (!backup[fd])
		return (NULL);
	line = set_line(&backup[fd]);
	if (!line && backup[fd])
	{
		free(backup[fd]);
		backup[fd] = NULL;
	}
	return (line);
}

/*#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	//int fd = open("text.txt", O_RDONLY);
	char *line;
	
	while ((line = get_next_line(42)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	//close(fd);
	return (0);
}*/
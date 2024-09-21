/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:49:57 by dangonz3          #+#    #+#             */
/*   Updated: 2024/06/18 11:51:57 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	*line[4096];
	char		buffer[BUFFER_SIZE +1];
	int			readbytes;
	char		*return_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	readbytes = 1;
	while (!ft_strchr(line[fd], '\n') && readbytes > 0)
	{
		readbytes = read(fd, buffer, BUFFER_SIZE);
		if (readbytes == -1)
			return (NULL);
		buffer[readbytes] = '\0';
		line[fd] = gnl_strjoin(line[fd], buffer);
		if (!line[fd])
			return (NULL);
	}
	return_line = gnl_cut_line(line[fd]);
	line[fd] = gnl_excess(line[fd]);
	return (return_line);
}

char	*gnl_cut_line(char *line)
{
	char	*return_line;
	int		i;
	int		j;

	i = 0;
	if (!line[0])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	return_line = ft_calloc(i + 2, sizeof(char));
	if (!return_line)
		return (NULL);
	j = -1;
	while (++j <= i)
		return_line[j] = line[j];
	if (line[i] == '\n')
		return_line[++i] = '\0';
	return (return_line);
}

char	*gnl_excess(char *line)
{
	char	*excess;
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (!line[i])
		return (free (line), NULL);
	excess = ft_calloc(ft_strlen(line) - i + 1, sizeof(char));
	if (!excess)
		return (NULL);
	while (line[i])
		excess[j++] = line[++i];
	excess[j] = '\0';
	free(line);
	return (excess);
}

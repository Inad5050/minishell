/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:19:33 by dani              #+#    #+#             */
/*   Updated: 2024/11/04 19:43:10 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	here_doc(char *end, int i, t_mini *m)
{
	int		pipefd[2];
	char	*line;
	char	*end_s;

	end_s = ft_strjoin(end, "\n");
	if (!end_s)
		m_exit("Ft_strjoin here_doc", m);
	if (pipe(pipefd) < 0)
		m_exit("Pipe here_doc", m);
	line = m_get_next_line(0, end_s);
	while (line && ft_strncmp(line, end_s, ft_strlen(end_s)))
	{
		ft_putstr_fd(line, pipefd[1]);
		free(line);
		line = m_get_next_line(0, end_s);
	}
	free(end_s);
	free(line);
	close(pipefd[1]);
	m->cmds[i].infile = pipefd[0];
}

char	*m_get_next_line(int fd, char *end_s)
{
	static char	*line;
	char		buffer[BUFFER_SIZE +1];
	int			readbytes;
	char		*return_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	readbytes = 1;
	while (!ft_strchr(line, '\n') && readbytes > 0)
	{
		readbytes = read(fd, buffer, BUFFER_SIZE);
		if (readbytes == -1)
			return (NULL);
		buffer[readbytes] = '\0';
		line = gnl_strjoin(line, buffer);
		if (!line)
			return (NULL);
	}
	return_line = gnl_cut_line(line);
	line = gnl_excess(line);
	if (!m_strncmp(return_line, end_s, ft_strlen(end_s)))
		free(line);
	return (return_line);
}

int	m_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (!str1 || !str2)
		return (-1);
	while (i < n && (str1[i] != '\0' || str2[i] != '\0'))
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

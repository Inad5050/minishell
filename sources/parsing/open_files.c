/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:50:28 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/16 21:19:21 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void here_doc(char *file, int i, t_mini *m)
{






	
	
}

int	here_doc(char *end, t_mini *m)
{
	int		pipefd[2];
	char	*line;
	char	*end_s;

	end_s = ft_strjoin(end, "\n");
	if (!end_s)
		m_exit("Couldn't allocate memory in here_doc", m);
	if (pipe(pipefd) < 0)
		m_exit("Couldn't pipe in here_doc", m);
	line = pi_get_next_line(0, end);
	while (line && ft_strncmp(line, end_s, ft_strlen(end_s)))
	{
		ft_putstr_fd(line, pipefd[1]);
		free(line);
		line = pi_get_next_line(0, end_s);
	}
	free(end_s);
	free(line);
	close(pipefd[1]);
	return (pipefd[0]);
}

char	*pi_get_next_line(int fd, char *end_s)
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
	if (!pi_strncmp(return_line, end_s, ft_strlen(end_s)))
		free(line);
	return (return_line);
}

int	pi_strncmp(const char *str1, const char *str2, size_t n)
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









void	open_files_aux(char *file, int is_outfile, int i, t_mini *m)
{
	if (!is_outfile)
	{
		if (!(m->cmds[i].append))
		{
			m->cmds[i].infile = open(file, O_RDONLY);
			if (m->cmds[i].infile == -1)
				m_exit("Couldn't open infile", m);
		}
		else if ((m->cmds[i].append))
			here_doc(file, i, m);
		return ;
	}
	if (is_outfile)
	{
		if (!(m->cmds[i].append))
			m->cmds[i].outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if ((m->cmds[i].append))
			m->cmds[i].outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (m->cmds[i].outfile == -1)
			m_exit("Couldn't open outfile", m);
	}
}

void	open_files(t_mini *m)
{
	int i;

	i = 0;
	while (i < m->cmd_count)
	{
		if (m->cmds[i].infile_name)
			open_files_aux(m->cmds[i].infile_name, 0, i, m);
		if (m->cmds[i].outfile_name)
			open_files_aux(m->cmds[i].outfile_name, 1, i, m);
	}
}

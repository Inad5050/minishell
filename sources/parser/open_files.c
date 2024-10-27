/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:50:28 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/25 17:23:57 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void here_doc(char *end, int i, t_mini *m) //cuando usamos << el char * en lugar de ser el file_name es sl string que nos indica que debemos dejar de leer.
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

int	open_files_aux(char *file, int is_outfile, int i, t_mini *m)
{
	if (!is_outfile) //si no es outfile es infile
	{
		if (!(m->cmds[i].append_in))
		{
			m->cmds[i].infile = open(file, O_RDONLY);
			if (m->cmds[i].infile == -1)
				return (m_error("Couldn't open infile", m), 0);
		}
		else if ((m->cmds[i].append_in))
			here_doc(m->cmds[i].infile_name, i, m);
	}
	if (is_outfile)
	{
		if (!(m->cmds[i].append_out))
			m->cmds[i].outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if ((m->cmds[i].append_out))
			m->cmds[i].outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (m->cmds[i].outfile == -1)
			return (m_error("Couldn't open outfile", m), 0);
	}
	return (1);
}

int	open_files(t_mini *m)
{
	int i;

	i = 0;
	while (i < m->cmd_count)
	{
		if (m->cmds[i].infile_name)
		{
			if(!(open_files_aux(m->cmds[i].infile_name, 0, i, m)))
				return (0);
		}
		if (m->cmds[i].outfile_name)
		{
			if(!(open_files_aux(m->cmds[i].outfile_name, 1, i, m)))
				return (0);
		}
		i++;
	}
	return (1);
}

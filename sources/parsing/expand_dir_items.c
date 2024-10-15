/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dir_items.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:08:35 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/14 16:25:43 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	dir_item_count(t_mini *m) //cuenta todos los archivos y directorios excluyendo los ocultos que empiezan por '.' .
{
	DIR				*dir;
	struct dirent	*t_dir; //es el tipo de dato que devuelve readdir(). readdir() almacena información sobre todos archivos y directorios del directorio actual.
	int				count;
	
	dir = opendir(".");
	if (!dir)
		m_exit("Cannot opendir in num_dir_items", m);
	count = 0;
	t_dir = readdir(dir);
	while (t_dir)
	{
		if (t_dir->d_name[0] != '.')
			count++;
		t_dir = readdir(dir);
	}
	closedir(dir); //similar a open cuando usas closedir() el puntero de opendir() vuelve a empezar desde el principio. Por lo que no afectara al siguiente opendir().
	return (count);
}

char	**fill_dir_items(char **dir_items, DIR *dir, t_mini *m)
{
	int				i;
	struct dirent	*t_dir; //es el tipo de dato que devuelve readdir(). readdir() almacena información sobre todos archivos y directorios del directorio actual.
	char			*dir_name;
	
	i = 0;
	t_dir = readdir(dir);
	while (t_dir)
	{
		if (t_dir->d_name[0] != '.') //excluye los ocultos que empiezan por '.' .
		{
			dir_name = ft_strdup(t_dir->d_name); //extrae el nombre del directorio de la estructura (t_dir) dónde readdir() lo ha almacenado.
			if (!dir_name)
				m_exit("Cannot assign memory in fill_dir_items", m);
			dir_items[i++] = dir_name;
		}
		t_dir = readdir(dir); //readdir "leera" el siguiente directorio cada vez que se le llame
	}
	dir_items[i] = NULL;
 	return (dir_items);
}

void	expand_dir_items(int index, t_mini *m)
{
	char	**dir_items; //donde almacenaremos los items del directorio actual excluyendo los archivos ocultos (empiezan por .*).
	int		item_num;
	DIR		*dir; //es el tipo de dato que devuelve opendir().
	
	item_num = dir_item_count(m);
	dir_items = ft_calloc(item_num + 1, sizeof(char *));
	if (!dir_items)
		m_exit("Cannot assign memory in get_dir_items", m);
	dir = opendir("."); //"." se refiere al directorio actual.
	if (!dir)
		m_exit("Cannot opendir in get_dir_items", m); //Hay que usar return cuando usamos m_error o lo aniquila todo como m_exit?
	dir_items = fill_dir_items(dir_items, dir, m);
	closedir(dir); //close(), como si hubieramos usado open().
	free(m->tokens[index]);
	m->tokens[index] = dir_items;
}

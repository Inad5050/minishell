/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir_items.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:08:35 by dangonz3          #+#    #+#             */
/*   Updated: 2024/10/02 21:14:04 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../../includes/minishell.h>

//dir_items = get_next_item(t_dir->d_name, dir_items, &dir_item_num, &i);

/* static char	**get_next_item(char *n, char *items[], size_t *it_siz, size_t *i)
{
	if (*it_siz == (*i + 2))
	{
		*it_siz += 10;
		items = ft_realloc_str_arr(items, *it_siz);
		if (items == NULL)
			return (NULL);
	}
	items[*i] = ft_strdup(n);
	if (items[*i] == NULL)
		return (ft_free_split(items));
	(*i)++;
	return (items);
}

static char	*get_items_sorted(char **unsorted)
{
	char	*items;
	int		i;

	items = NULL;
	unsorted = ft_sort_str_arr(unsorted);
	i = 0;
	while (unsorted[i])
	{
		items = ft_append(&items, unsorted[i]);
		if (items == NULL)
			return (ft_free_split(unsorted));
		items = ft_append(&items, " ");
		if (items == NULL)
			return (ft_free_split(unsorted));
		i++;
	}
	ft_free_split(unsorted);
	return (items);
}

char	*get_dir_items(void)
{
	DIR				*d;
	struct dirent	*dir;
	char			**items;
	size_t			items_size;
	size_t			i;

	d = opendir(".");
	if (d == NULL)
		return (NULL);
	i = 0;
	items_size = 10;
	dir = readdir(d);
	items = ft_calloc(items_size + 1, sizeof(*items));
	if (items == NULL)
		return (NULL);
	while (dir != NULL)
	{
		if (dir->d_name[0] != '.')
			items = get_next_item(dir->d_name, items, &items_size, &i);
		if (items == NULL)
			return (NULL);
		dir = readdir(d);
	}
	closedir(d);
	return (get_items_sorted(items));
} */

int	dir_item_count(t_mini *m)
{
	DIR				*dir;
	struct dirent	*t_dir;
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
	closedir(dir);
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
		if (t_dir->d_name[0] != '.') //"." se refiere al directorio actual.
		{
			dir_name = ft_strdup(t_dir->d_name);
			if (!dir_name)
				m_exit("Cannot assign memory in fill_dir_items", m);
			dir_items[i++] = dir_name;
		}
		t_dir = readdir(dir); //readdir "leera" el siguiente directorio cada vez que se le llame
	}
	dir_items[i] = NULL;
 	return (dir_items);
}

void	get_dir_items(int index, t_mini *m)
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

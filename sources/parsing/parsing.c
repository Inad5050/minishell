/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:54:28 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/22 20:24:48 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*parsing(t_mini *m)
{
	int	tokens;
	
	tokens = 0;
	if (!m->input)
		return (ft_printf("exit\n"), NULL); //cuando el input del usuario es NULL terminamos la mini. Es este el comportamiento esperado?
	if (m->input[0] != '\0')
		add_history(m->input); //función del sistema relacinada con la gestión de read_line. Añade el argumento a la lista del historial de read_line. Se usa write_history para guardar el historial en el archivo seleccionad. Y read_history para leerlo.
	tokens = count_words(m);
	m->input_split = ft_calloc(tokens + 1, sizeof(char *));
	m->input_split[tokens] = NULL;
	fill_split(m);
	
	


	free(m->input_split); //habria que eliminar todos los strings dentro del split, crear una funcion
}

int	count_tokens(t_mini *m)
{
	char	*str;
	int		i;
	int		tokens;
	
	str = m->input;
	i = 0;
	while (str[i])
	{
		while (((9 <= str[i] && str[i] <= 13) || str[i] == 32) && str[i])
			i++;
		if (problematic_chars(str[i++], m))
			continue;
		if (!(9 <= str[i] && str[i] <= 13) && !(str[i] == 32)) && ((9 <= str[i + 1] && str[i + 1] <= 13) || (str[i + 1] == 32)) //WTF
			tokens++;
		i++;	
	}
	return (tokens);
}

void	fill_split(t_mini *m)
{
	int		i;
	int		start;
	int		token_num;
	char	*token;
	
	i = 0;
	token_num = 0;
	while (m->input[i])
	{
		while (((9 <= m->input[i] && m->input[i] <= 13) || m->input[i] == 32) && m->input[i])
			i++;
		start = i;
		if (problematic_chars(m->input[i++], m))
			continue;
		if (!(9 <= m->input[i] && m->input[i] <= 13) && !(m->input[i] == 32)) && ((9 <= m->input[i + 1] && m->input[i + 1] <= 13) || (m->input[i + 1] == 32)) //WTF
		{
			token = ft_strdup()
			m->input_split[token_num++] = ft_strdup()
		}
		i++;	
	}


}

		if (problematic_chars(str[i++], m))
			continue;
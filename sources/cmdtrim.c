/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:24:48 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/18 17:25:20 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**ft_cmdtrim(char const *s, char *set);
static char	**ft_fill_array(char **aux, char const *s, char *set, int i[3]);
static int	ft_count_words(const char *s, char *c, int i[2]);
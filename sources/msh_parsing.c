/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 18:29:14 by amulin            #+#    #+#             */
/*   Updated: 2016/09/16 15:53:32 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_normalize_blanks(char *c)
{
	if (*c == '\t')
		*c = ' ';
}

/*
 *	This function takes one command line from stdin, replaces tabs with
 *	spaces, then splits the line into an array of strings using
 *	spaces as separator.
*/
char	**msh_parse_line(char *line)
{
	char	**tab;
	char	*buf;
	int		i;

	ft_striter(line, &msh_normalize_blanks);

	buf = ft_strtrim(line);
	if (!buf)
		msh_error_exit("malloc allocation fail on ft_strtrim\n", -1);
	if (MSH_DEBUG_MODE)
		ft_printf("ns_parse_line, normalized and trimmed line = '%s'\n", buf);
	tab = ft_strsplit(buf, ' ');
	ft_strdel(&buf);
	i = 0;
	while (tab && tab[i])
	{
//		if (i == 0 && !ft_strcmp(tab[i], "exit"))
//			exit(0);
		if (MSH_DEBUG_MODE)
			ft_printf("tab[%d] = %s\n", i, tab[i]);
		i++;
	}
	return (tab);
}

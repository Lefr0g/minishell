/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 18:28:44 by amulin            #+#    #+#             */
/*   Updated: 2016/09/15 18:28:45 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*msh_getenv(const char *name, char **environ)
{
	char		*str;
	int			i;

	if (!name && !ft_strlen(name))
		return (NULL);
	i = 0;
	while (environ && environ[i])
	{
		if (ft_strstr(environ[i], name) == &environ[i][0])
		{
			str = ft_strnew(ft_strlen(environ[i]));
			ft_strncpy(str, &environ[i][ft_strlen(name) + 1],
					ft_strlen(environ[i]) - (ft_strlen(name) + 1));
			return (str);
		}
		i++;
	}
	return (NULL);
}

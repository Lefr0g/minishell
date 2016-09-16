/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 18:07:18 by amulin            #+#    #+#             */
/*   Updated: 2016/09/15 18:08:18 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*msh_is_builtin(char *cmd, char **builtins)
{
	int	i;

	i = 0;
	while (i < MSH_BUILTINS_ARRAY_SIZE)
	{
		if (!ft_strcmp(cmd, builtins[i]))
			return (builtins[i]);
		i++;
	}
	return (NULL);
}

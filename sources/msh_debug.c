/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 18:28:33 by amulin            #+#    #+#             */
/*   Updated: 2016/09/15 18:28:35 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_debug_print_color(char *str, char *color)
{
	if (MSH_DEBUG_MODE)
		ft_putstr_color_each(str, color);
}

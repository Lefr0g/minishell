#include "minishell.h"

void	msh_debug_print_color(char *str, char *color)
{
	if (MSH_DEBUG_MODE)
		ft_putstr_color_each(str, color);
}

#include "minishell.h"

int		main(int ac, char **av)
{
	(void)av;
	/*
	i = -1;
	while (environ[++i])
		ft_printf("%s\n", environ[i]);
	*/

	if (ac != 1)
		ft_putstr("Invalid argument. This program doesn't take any.\n");
	else
	{
		msh_main_loop();
	}
	return (0);
}

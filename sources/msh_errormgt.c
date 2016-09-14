#include "minishell.h"

void	msh_error_exit(const char *msg, int ret_value)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(ret_value);
}

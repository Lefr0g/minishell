

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "libft_extra.h"
# include <sys/wait.h> // explicitly needed to compile on Linux

# define PROG_NAME "minishell"

# define MSH_DEBUG_MODE 0

// check out /usr/include/sysexits.h for some error code definitions
// More info on http://tldp.org/LDP/abs/html/exitcodes.html
# define EX_ILLEG 127 // command not found

/*
**	main.c
*/
int		main(int ac, char **av);

/*
**	msh_parsing.c
*/
void	msh_normalize_blanks(char *c);
char	**msh_parse_line(char *line);

/*
**	msh_process.c
*/
int		msh_main_loop(void);

/*
**	msh_exec.c
*/
int		msh_path_loop_exec(char *file, char **argv, char **envp);

/*
**	msh_prompt.c
*/
int		msh_print_prompt(void);

/*
**	msh_env.c
*/
char	*msh_getenv(const char *str);

/*
**	msh_errormgt.c
*/
void	msh_error_exit(const char *msg, int ret_value);

/*
**	msh_debug.c
*/
void	msh_debug_print_color(char *str, char *color);

/*
**	libft_addition.c
*/
int		ft_putstr_color_each(char *str, char *color);


#endif

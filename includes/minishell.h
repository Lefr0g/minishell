/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 18:30:18 by amulin            #+#    #+#             */
/*   Updated: 2016/09/15 18:30:21 by amulin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "libft_extra.h"
# include <sys/wait.h> // explicitly needed to compile on Linux

# define PROG_NAME "minishell"

# define MSH_DEBUG_MODE 0
# define MSH_BUILTINS_ARRAY_SIZE 7

// check out /usr/include/sysexits.h for some error code definitions
// More info on http://tldp.org/LDP/abs/html/exitcodes.html
# define EX_ILLEG 127 // command not found

typedef struct	s_msh_vars
{
	char	**environ;
	char	**locales;
	char	**builtins;
	char	*cwd;
}				t_msh_vars;

/*
**	main.c
*/
int		main(int ac, char **av);

/*
**	msh_init.c
*/
int		msh_init_vars(t_msh_vars *v);

/*
**	msh_parsing.c
*/
void	msh_normalize_blanks(char *c);
char	**msh_parse_line(char *line);

/*
**	msh_process.c
*/
int		msh_main_loop(t_msh_vars *v);

/*
**	msh_exec.c
*/
int		msh_getcwd(t_msh_vars *v);
int		msh_exec_cwd(char *file, char **argv, t_msh_vars *v);
int		msh_exec(char *file, char **argv, t_msh_vars *v);

/*
**	msh_prompt.c
*/
int		msh_print_prompt(void);

/*
**	msh_env.c
*/
char	*msh_getenv(const char *str, char **environ);

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
char	*ft_strarray_chr(char *needle, char **haystack);


#endif

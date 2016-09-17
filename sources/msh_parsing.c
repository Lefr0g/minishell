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
 *	According to https://www.gnu.org/software/bash/manual/bash.html#Shell-Syntax
 *	Bash parsing:
 *	1. Reads its input from a file (see Shell Scripts), from a string supplied
 *	as an argument to the -c invocation option (see Invoking Bash), or from 
 *	the user’s terminal.
 *	2. Breaks the input into words and operators, obeying the quoting rules
 *	described in Quoting. These tokens are separated by metacharacters.
 *	Alias expansion is performed by this step (see Aliases).
 *	3. Parses the tokens into simple and compound commands (see Shell Commands).
 *	4. Performs the various shell expansions (see Shell Expansions), breaking
 *	the expanded tokens into lists of filenames (see Filename Expansion) and
 *	commands and arguments.
 *	5. Performs any necessary redirections (see Redirections) and removes
 *	the redirection operators and their operands from the argument list.
 *	6. Executes the command (see Executing Commands).
 *	7. Optionally waits for the command to complete and collects its exit
 *	status (see Exit Status).
 *
 *	TODO: implement the flow:
 *	1. Quoting rule: string -> words / operators (tokens)
 *		- Escape characters
 *		- Single quotes
 *		- Double quotes
 *		- ANSI quotes
 *	2. Alias expansion
 *	3. Parse tokens -> simple commands / compound commands
 *	4. Shell expansions
 *	5. Redirections
 *	6. Execution
 *	7. loop back
 *
 *	Info
 *	Bash metacharacters: A character that, when unquoted, separates words
 *	' ', ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’.
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

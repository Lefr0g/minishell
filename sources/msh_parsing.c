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
**	Cut the given line into a string array according to the double quotes
**	parsing rule
*/

char	**msh_doublequotes(char *line)
{
	(void)line;
	char	**array;

	array = ft_strarray_new(3);
	array[0] = ft_strdup("Hello there");
	array[1] = ft_strdup("wubba lubba dub dub");
	array[2] = NULL;
	int		i;

	i = 0;
	while (array[i])
	{
		ft_printf("array[%d] = %s\n", i, array[i]);
		i++;
	}
	array = ft_strarray_add(&array, line);
	i = 0;
	while (array[i])
	{
		ft_printf("array[%d] = %s\n", i, array[i]);
		i++;
	}
	ft_printf("End of msh_doublequotes\n");
	return (array);
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
 *
 *
 *	si ('\' a la fin)
 *		gnl - continuer la lecture sur stdin
 *	si ('"')
 *		rechercher le suivant (sauf \") et dupliquer la chaine sans les EC
 *			si pas de suivant, continuer lecture stdin (ajouter dquote>)
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
	
//	tab = ft_strsplit(buf, ' ');
	
	tab = msh_doublequotes(line);

	ft_printf("Check 0\n");
	ft_strdel(&buf);
	ft_printf("Check 1\n");
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulin <amulin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 18:29:14 by amulin            #+#    #+#             */
/*   Updated: 2016/09/26 16:51:39 by amulin           ###   ########.fr       */
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
 *
 *
 *	si ('\' a la fin)
 *		gnl - continuer la lecture sur stdin
 *	si ('"')
 *		rechercher le suivant (sauf \") et dupliquer la chaine sans les EC
 *			si pas de suivant, continuer lecture stdin (ajouter dquote>)i
 *
 *	Update:
 *	These functionnalities are overkill for minishell. For this project we
 *	will keep our parsing as simple as possible.
*/
char	**msh_parse_line_old(char *line)
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

//	Quoting / escaping and other advanced string features are out of scope
//	for minishell. To be implemented on 21sh / 42sh instead.	
//	tab = msh_doublequotes(line);

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

/*
**	Experimental: this alternative is designed to support multiple commands
**	on the same line, separated by ;
*/
char	***msh_parse_line(char *line)
{
	char	***args;
	char	*buf;
	int		*i;

	if (msh_parse_line_init_vars(&args, line, &i))
		return (NULL);
	while (line[++i[0]])
		if ((line[i[0]] == ';' && i[0] > 0 && line[i[0] - 1] != '\\')
				|| (!line[i[0] + 1]))
		{
			buf = ft_strnew(i[0] - i[1] + 1);
			ft_strncpy(buf, &line[i[1]], i[0] - i[1] + (!line[i[0] + 1]));
			ft_striter(buf, &msh_normalize_blanks);
			msh_escape_semicolon(buf);
			args[i[2]] = ft_strsplit(buf, ' ');
			ft_strdel(&buf);
			i[2]++;
			i[0]++;
			i[1] = i[0];
		}
	args[i[2]] = NULL;
	i[0] = 0;

	while (MSH_DEBUG_MODE && args[i[0]])
	{
		i[1] = 0;
		while (args[i[0]][i[1]])
		{
			ft_printf("args[%d][%d] = %s\n", i[0], i[1], args[i[0]][i[1]]);
			i[1]++;
		}
		ft_putchar('\n');
		i[0]++;
	}
	free(i);
	return (args);
}

int		msh_parse_line_init_vars(char ****cmds, const char *line, int **i)
{
	int	cnt;

	if (!(*i = (int*)ft_memalloc(sizeof(int) * 3)))
		return (1);
	cnt = 1;
	cnt += ft_strcnt((char*)line, ';');
	if (!(*cmds = (char***)malloc(sizeof(char**) * cnt + 1)))
		return (1);
	i[0][0] = -1;
	i[0][2] = 0;
	return (0);
}

/*
**	This function is designed to remove single ';' that may remain at the
**	start and end of the string, and also to transform escaped "\;" into
**	single ';'
**	Ideally no memory reallocation will be needed
*/

char	*msh_escape_semicolon(char *str)
{
	int		i;
	int		j;
	char	*cpy;

	if (!ft_strcnt(str, ';'))
		return (str);
	cpy = ft_strdup(str);
	ft_bzero(str, ft_strlen(cpy));
	i = 0;
	j = 0;
	while (cpy[i])
	{
		if (cpy[i] == ';' && (!i || !cpy[i + 1]))
			i++;
		else if (cpy[i] == '\\' && cpy[i + 1] == ';')
		{
			str[j] = ';';
			i += 2;
			j++;
		}
		else
			str[j++] = cpy[i++];
	}
	return (str);
}

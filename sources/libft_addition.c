#include "libft_extra.h"

/*
 *	Subfunction for ft_find_and_replace, this function counts the number of
 *	occurrences of the string 'needle' within the strinf 'haystack'
*/
int		ft_strstrcnt(char *haystack, char *needle)
{
	int		cnt;
	char	*buf;

	cnt = 0;
	buf = haystack;
	while (buf)
	{
		if ((buf = ft_strstr(buf, needle)))
		{
			buf += sizeof(char) * ft_strlen(needle);
			cnt++;
		}
		ft_printf("cnt = %d\n", cnt);
	}
	return (cnt);
}

/*
 *	Find-and-replace within a string
 *	This function replaces the 'n'th occurrence of the string 'needle' with
 *	the 'new' substring wthin the 'haystack'
 *	If n is 0, all occurrences will be replaced.
 *	A pointer to the new string is returned
 *
 *	Algo de remplacement (reco traitement char par char) :
 *		- creer un buffer suffisamment large
 *		- localiser la sous-chaine
 *		- copier le debut de la chaine dans le buffer
 *		- copier le new a la suite dans le buffer
 *		- sauter l'espace correspondant au needle
 *		- copier la suite de la chaine
*/
char	*ft_find_and_replace(char *haystack, char *needle, int n, char *new)
{
//	char	*pre;
//	char	*post;
	char	*buf;
	int		i;
	int		j;
	int		k;

	(void)new;
	i = 0;
	if (n < 0 || !haystack || !needle || !ft_strstrcnt(haystack, needle) ||
			(n && ft_strstrcnt(haystack, needle) < n))
		return (NULL);

	i = !n ? ft_strstrcnt(haystack, needle) : 1;
	buf = ft_strnew(ft_strlen(haystack) + (ft_strlen(new) * i));

	i = 0;
	j = 0;
	k = 0;
	while (haystack[j])
	{
		if (!ft_strncmp(&haystack[j], needle, ft_strlen(needle)) && ++k &&
				(!n || n == k))
		{
			ft_strcat(buf, new);
			i += ft_strlen(new);
			j += ft_strlen(needle);
		}
		else
		{
			buf[i] = haystack[j];
			i++;
			j++;
		}
	}

	return (buf);
}

/*
 *	Multiprocess-compatible string color management, writing to stdout
 *	Recommend using ANSI color codes as defined in libft_extra.h
*/

int		ft_putstr_color_each(char *str, char *color)
{
	int		i;
	char	*out;

	out = ft_strnew(10);
	i = 0;
	if (ft_strlen(color) != 5)
		return (-1);
	while (str[i])
	{
		ft_strcat(out, color);
		ft_strncat(out, &str[i], 1);
		ft_strcat(out, ANSI_RESET);
		ft_putstr(out);
		ft_strclr(out);
		i++;
	}
	ft_strdel(&out);
	return (i);
}

/*
**	Alias for ft_find_double_str, which name sucks
**	ft_strarray_chr() - locate string in string array
*/

char	*ft_strarray_chr(char *needle, char **haystack)
{
	return (ft_find_double_str(needle, haystack));
}

/*
**	Counts the total number of occurrences of the char 'c' within the string
*/

int		ft_strcnt(char *str, int c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == (unsigned char)c)
			count++;
	}
	return (count);
}

char	**ft_strarray_new(size_t size)
{
	char	**array;
	size_t	i;

	if (!(array = (char**)malloc(sizeof(char*) * size + 1)))
		return (NULL);
	i = 0;
	while (i <= size)
	{
		array[i] = NULL;
		i++;
	}
	return (array);
}

char	**ft_strarray_add(char ***in_array, char *new)
{
	int		i;
	char	**out_array;

	i = 0;
	if (!in_array)
		i = 1;
	else
	{
		while (in_array[0][i])
			i++;
	}
	out_array = ft_strarray_new(i + 2);
	i = 0;
	while (in_array[0][i])
	{
		out_array[i] = ft_strdup(in_array[0][i]);
		i++;
	}
	out_array[i] = ft_strdup(new);
	ft_strarray_del(in_array);
	return (out_array);
}

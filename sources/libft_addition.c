#include "libft_extra.h"

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
	while (i < size)
	{
	/*
		if (!(array[i] = ft_strnew(1)))
		{
			ft_strarray_del(&array);
			return (NULL);
		}
	*/
		array[i] = NULL;
		i++;
	}
	return (array);
}

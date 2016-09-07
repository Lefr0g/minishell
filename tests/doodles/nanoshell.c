#include "libft.h"
#include "libft_extra.h"

char	*concatenate_args(int ac, char **av)
{
	int		i;
	int		len;
	char	*result;
	char	*buf;

	i = 0;
	len = 0;
	while (++i < ac)
		len += ft_strlen(av[i]);
	buf = ft_strnew(len + 1);
	i = 0;
	while (++i < ac)
	{
		ft_strcat(buf, av[i]);
		ft_strcat(buf, " ");
	}
	result = ft_strtrim(buf);
	ft_strdel(&buf);
	return (result);
}

int		main(int ac, char **av)
{
	int		i;
	int		sub_ac;
	char	*strbuf;
	char	**sub_av;


//	ft_bzero(strbuf, 11);
	if (ac == 1)
	{
		ft_putstr("please enter an argument\n");
		return (0);
	}
	else
	{
		sub_ac = ac - 1;
		sub_av = (char**)malloc(sizeof(char*) * ac);
		i = 0;

		while (i < ac)
		{
			sub_av[i] = av[i + 1];
			i++;
		}
		sub_av[i] = NULL;

		av[0] = NULL;
		ft_printf("Executing command '%s' given as parameter :\n", av[1]);

		// TODO: recherche et essais successifs dans le PATH
		execve(sub_av[0], sub_av, NULL);
		ft_printf("Execution completed\n");
/*
		strbuf = concatenate_args(ac, av);
		if (strbuf)
			ft_printf("arguments : \"%s\"\n", strbuf);
*/
	}
	ft_strdel(&strbuf);
	return (0);
}

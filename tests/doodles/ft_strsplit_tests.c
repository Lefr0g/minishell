#include "libft.h"

int	main(int argc, char **argv)
{
	char	**tab;
	int		i;

	if (argc == 1)
	{
		ft_putstr("Usage a.out \"string splitted with spaces\"\n");
		tab = ft_strsplit("***salut****!**", '*');
//		tab = ft_strsplit("salut !", ' ');
	}
	else
	{
		tab = ft_strsplit(argv[1], ' ');
		ft_putendl("split done.");
	}
	i = 0;
	while (tab && tab[i])
	{
		ft_putstr("tab[");
		ft_putnbr(i);
		ft_putstr("] = \"");
		ft_putstr(tab[i]);
		ft_putstr("\"\n");
		i++;
	}
	return (0);
}

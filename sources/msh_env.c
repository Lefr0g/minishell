#include "minishell.h"

char	*msh_getenv(const char *name)
{
	extern char	**environ;
	char		*str;
	int			i;

	if (!name && !ft_strlen(name))
		return (NULL);
	i = 0;
	while (environ && environ[i])
	{
		if (ft_strstr(environ[i], name) == &environ[i][0])
		{
			str = ft_strnew(ft_strlen(environ[i]));
			ft_strncpy(str, &environ[i][ft_strlen(name) + 1],
					ft_strlen(environ[i]) - (ft_strlen(name) + 1));
			return (str);
		}
		i++;
	}
	return (NULL);
}

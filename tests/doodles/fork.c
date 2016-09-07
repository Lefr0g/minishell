#include "libft.h"
#include "libft_extra.h"

# define LOOP_LIMIT 20

//char	**get_

int	main(int ac, char **av)
{
	pid_t	proc_id;
	pid_t	ret_child;
	int		stat_loc;
	int		i;
	char	*cmd = "ls";
	extern char **environ;

	if (ac == 1)
		ft_printf("%s: no arguments given\n", av[0]);
//	ft_printf("Sizeof(pid_t) = %d, sizeof(int) = %d\n", sizeof(pid_t),
//			sizeof(int));
	proc_id = fork();
	i = -1;
	if (!proc_id)
	{
		ft_printf("This is the child process\n");
		while (++i <= LOOP_LIMIT)
			ft_printf("Child, i = %d\n", i);
		ft_printf("Executing ls command\nls arguments are:\n");
		i = -1;
		while (av[++i])
			ft_printf("av[%d] = %s\n", i, av[i]);
		i = execve("/bin/ls", av, NULL);
		ft_printf("execve returned %d\n", i);
	}
	else
	{
		ft_printf("This is the parent process, child pid = %d\n", proc_id);
		ft_printf("Waiting for child process to complete...\n");
		ret_child = wait(&stat_loc);
		ft_printf("Child process completed, return value = %d\n", ret_child);
		ft_printf("stat_loc = %d\n", stat_loc);
		if (WIFEXITED(stat_loc))
			ft_printf("Process terminated normally\n");
		else if (WIFSIGNALED(stat_loc))
			ft_printf("Process terminated due to receipt of a signal\n");
		else if (WIFSTOPPED(stat_loc))
			ft_printf("Process has stopped and can be restarded\n");
		else
			ft_printf("Process status unknown\n");
		while (++i <= LOOP_LIMIT)
			ft_printf("Parent, i = %d\n", i);
	}
	sleep(5);
	return (0);
}

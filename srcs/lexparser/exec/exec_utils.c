#include "sh21.h"
#include "lexparser.h"
#include "builtins_list.h"

/*
** So, let's talk about pipes:
** 1) If only PIPED_OUT -- create pipe
** 2) If only PIPED_IN -- delete pipe
*/

/*
** consider changing architecture to... well, something else
*/

int		exec_clean(char **path, t_ltree *pos, int exit_status)
{
	if ((exit_status == -2) && (pos->flags) != ERR_CMDEXEC)
		errono(ERR_CMDNOTFOUND, ERR_CMDNOTFOUND, *pos->ar_v);
	if (path && *path)
		free(*path);
	return (exit_status);
}

/*
** Check if programm to start is buildin and if it is - start builtins
*/

int		ft_builtins_check(t_ltree *pos, int flag)
{
	int	i;
	int	exit;

	i = 0;
	while (g_builtins[i])
	{
		if (!ft_strcmp(pos->ar_v[0], g_builtins[i]))
		{
			if (flag)
			{
				exit = g_builtins_func[i](pos);
				var_exit_status(exit);
			}
			return (i);
		}
		i++;
	}
	return (-1);
}

int		fd_list_process(t_ltree *pos, int mode)
{
	t_list		*fd_list;
	t_fd_redir	*redir;

	if (!mode)
	{
		std_save(0);
		fd_list = pos->fd;
		while (fd_list)
		{
			redir = (t_fd_redir *)fd_list->content;
			if (redir->fd_old != CLOSE)
				dup2(redir->fd_old, redir->fd_new);
			else
			{
				dup2(redir->fd_new, redir->fd_new);
				close(redir->fd_new);
			}
			fd_list = fd_list->next;
		}
	}
	else
		std_save(1);
	return (0);
}

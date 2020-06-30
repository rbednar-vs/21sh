#include "sh21.h"
#include "builtins.h"

static int	sorting_vars(t_path **root, size_t *len)
{
	int		i;
	int		li;
	int		sy;

	i = -1;
	while (g_env[++i])
		insert(g_env[i], root, len);
	i = -1;
	while (g_lovar[++i])
		insert(g_lovar[i], root, len);
	li = variables_search(g_rdovar, &sy, "42SH=");
	i = li - 1;
	while (g_rdovar[++i])
		insert(g_rdovar[i], root, len);
	return (0);	
}

int			btin_set(void)
{
	t_path	*root;
	char	**list;
	size_t	len;
	int 	max;

	root = NULL;
	list = NULL;
	len = 0;
	sorting_vars(&root, &len);
	list = ft_add_block(&root, len, &max);
	ft_path_free(&root);
	max = -1;
	while(list[++max])
		ft_putendl(list[max]);
	ft_arrdel(list);
	return (0);	
}
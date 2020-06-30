#include "sh21.h"
#include "lexparser.h"
#include "builtins_list.h"

char	**path_parse(void)
{
	char	*path_value;
	char	**ret;

	if (!(path_value = get_env("PATH")))
		return (0);
	ret = ft_strsplit(path_value, ':');
	free(path_value);
	return (ret);
}

char	*form_path(char *ret, char *env_path, char *name)
{
	ft_bzero(ret, ft_strlen(env_path) + ft_strlen(name) + 2);
	ft_strcpy(ret, env_path);
	ft_strcat(ret, "/");
	ft_strcat(ret, name);
	if (access(ret, X_OK) == -1)
	{
		free(ret);
		ret = 0;
	}
	return (ret);
}

char	*locate_file(char *env_path, char *name, char **to_clean)
{
	struct dirent	*entity;
	char			*ret;
	DIR				*path;

	ret = 0;
	path = opendir(env_path);
	if (path == NULL)
		return (NULL);
	while ((entity = readdir(path)))
	{
		if (!ft_strcmp(entity->d_name, name))
		{
			if (!(ret = (char *)malloc(ft_strlen(env_path) + ft_strlen(name) + 2))) /* You shoud use Vlada's awesome function */
			{
				free_vec(to_clean);
				closedir(path);
				return (0);
			}
			ret = form_path(ret, env_path, name);
			if (ret)
				break;
		}
	}
	closedir(path);
	return (ret);
}

/*
** This is "just executable name case". We should check all directories in $PATH, find first match
** and check its accessibility
*/

char	*path_search(char *name)
{
	char			**path_array;
	char			**to_clean;
	char			*ret;

	if (!(path_array = path_parse()))
		return (0);
	to_clean = path_array;
	while(*path_array)
	{
		ret = locate_file(*path_array, name, to_clean);
		if (ret)
			break;
		path_array++;
	}
	free_vec(to_clean);
	if (!ret)
		errno(ERR_CMDNOTFOUND, ERR_NOCMD, name);
	return (ret);  /* Returns zero if we did not find anything */
}

/*
** Here we should find check and return execpath
*/

char	*path_init(char **exec_av)
{
	char *ret;

	if (!ft_strchr(*exec_av, '/')) /* Builtin or $PATH case */
		ret = path_search(*exec_av);
	else /* Execution path case */
	{
		if (access(*exec_av, F_OK) == -1)
		{
			errno(ERR_CMDNOTFOUND, ERR_NOFILEDIR, *exec_av);
			return (0);
		}
		else if (access(*exec_av, X_OK) == -1)
		{
			errno(ERR_CMDEXEC, 0, *exec_av);
			return (0);
		}
		ret = ft_strdup(exec_av[0]);
	}
	return (ret); /* ret could be NULL */
}

#include "sh21.h"
#include "help_lib.h"

size_t			ft_strlenchri(const char *s, char c)
{
	size_t		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}
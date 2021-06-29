#include "minishell.h"

static char	*end_strjoin(size_t *i, char **rs, char **add)
{
	int	j;

	if (*add)
	{
		j = 0;
		while ((*add)[j])
		{
			(*rs)[*i] = (*add)[j];
			j++;
			(*i)++;
		}
		free(*add);
		*add = NULL;
	}
	(*rs)[*i] = '\n';
	(*rs)[++(*i)] = '\0';
	return (*rs);
}

char	*strjoin_here_doc_parsing(char **buff, char **add)
{
	char	*rs;
	size_t	i;
	int		size;

	if (*buff)
		size = ft_strlen(*buff) + ft_strlen(*add) + 2;
	else
		size = ft_strlen(*add) + 2;
	rs = ft_calloc(size, sizeof(1));
	if (!rs)
		return (0);
	i = 0;
	if (*buff)
	{
		while ((*buff)[i])
		{
			rs[i] = (*buff)[i];
			i++;
		}
		free(*buff);
		*buff = NULL;
	}
	return (end_strjoin(&i, &rs, add));
}

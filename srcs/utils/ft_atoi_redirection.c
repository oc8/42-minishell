#include "minishell.h"

int	ft_atoi_redirection(const char *nptr, t_type_lex type)
{
	long long	rs;
	int			i;

	i = 0;
	if (!ft_isdigit(nptr[i]))
	{
		if (type == REDIR_IN)
			rs = 0;
		else if (type == REDIR_OUT || type == APP_REDIR_OUT)
			rs = 1;
		return (rs);
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		rs = rs * 10 + (nptr[i++] - '0');
		if (rs > INT_MAX)
			return (INT_MAX);
	}
	return (rs);
}

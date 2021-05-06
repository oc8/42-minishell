#include "libft.h"

void	ft_switch(void *v1, void *v2)
{
	void	*temp;

	temp = v1;
	v1 = v2;
	v2 = temp;
}

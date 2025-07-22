#include "treasure_venture.h"

size_t	count_array(void **arr)
{
	size_t	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		++i;
	return (i);
}

void	free_array(void **arr, void (*free_fct)(void *))
{
	size_t	i;

	if (!arr)
		return ;
	if (free_fct)
	{
		i = 0;
		while (arr[i])
		{
			free_fct(arr[i]);
			++i;
		}
	}
	free(arr);
	return ;
}

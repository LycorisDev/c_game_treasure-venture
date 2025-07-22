#include "treasure_venture.h"

size_t	count_arr(void **arr)
{
	size_t	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		++i;
	return (i);
}

void	free_arr(void **arr, void (*free_fct)(void *))
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

void	remove_arr_elems(void **arr, size_t from, size_t to,
			void (*free_fct)(void *))
{
	size_t	i;

	if (!arr || from > to)
		return ;
	i = from;
	while (arr[i] && i <= to)
	{
		if (free_fct)
			free_fct(arr[i]);
		++i;
	}
	while (arr[i])
	{
		arr[from] = arr[i];
		++from;
		++i;
	}
	arr[from] = 0;
	return ;
}

#include "push_swap.h"

void	ft_move_until_orded(t_struct *data)
{
	int	div;
	int	i;
	int	ix;

	div = data->size_a / 2;
	i = -1;
	while (++i < data->size_a)
		if (data->ar_a[i] == 1)
			ix = i;
	if (ix < div)
		while (data->ar_a[0] != 1)
			ft_rotate_a(data);
	else
		while (data->ar_a[0] != 1)
			ft_rev_rotate_a(data);
}

int	ft_check_set(int *arr, int c, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		if (arr[i] == c)
			return (1);
	return (0);
}

int	push_in_b(t_struct *data, int pos, int val, int *flag)
{
	int	div;

	div = data->size_a / 2;
	if (pos < div)
		while (data->ar_a[0] != val)
			ft_rotate_a(data);
	else
		while (data->ar_a[0] != val)
			ft_rev_rotate_a(data);
	*flag = 1;
	ft_push_b(data);
	return (0);
}

int	get_max_move(int *arr, int size, int x)
{
	int	i;
	int	max;

	i = -1;
	max = 0;
	while (++i < size)
		if (arr[i] > max && arr[i] < x)
			max = arr[i];
	return (max);
}

int	ft_get_min_arr(t_moves *moves, int size)
{
	int	i;
	int	ix;
	int	min;

	i = -1;
	min = 0;
	ix = 0;
	while (++i < size)
	{
		if (min > moves[i].sum || i == 0)
		{
			ix = i;
			min = moves[i].sum;
		}
	}
	return (ix);
}

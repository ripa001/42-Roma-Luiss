#include "pusciacca.h"

// int findComb(int *arr, int *comb, int count, int x)
// {
// 	int i;
// 	int k;
// 	int j;
// 	int c;

// 	i = x;
// 	comb = malloc(sizeof(int) * count);
// 	j = -1;
// 	k = -1;
// 	c = 1;
// 	while (++i != x)
// 	{
// 		if (arr[i] == arr[j] + 1)
// 		{
// 			comb[++k] = arr[i];
// 			c += 1;
// 			j = i;
// 		}
// 		if (i == count)
// 			i = -1;
// 	}
// 	i = x;
// 	while (++i != )
// 	{
// 		if (arr[i] == x + 1)
// 		{
// 			comb[++j] = arr[i];
// 			c += 1;
// 			x = arr[i];
// 		}
// 	}
// 	return (c);
// }
void emptyarr(t_arrt arrt)
{
	int j;

	j = -1;
	while (++j < arrt.count)
		arrt.arr[j] = 0;
}

int checkarr(t_arrt *arrt, int i, int x)
{
	int	j;

	j = -1;
	while (++j < i - 1)
	{
		printf("%d, %d\n", j, i);
		if (arrt[j].arr[arrt[i].count] < x)
			return (0);
	}
	return (1);
}

int checkrevarr(t_arrt *arrt, int i, int x)
{
	int	j;

	j = -1;
	while (++j < i - 1){
		printf("%d, %d -\n", arrt[j].arr[0], j);
		if (arrt[j].arr[arrt[i].count] > x)
			return (0);}
	return (1);
}

void swaparr(t_arrt *arrt, int c, int lines)
{
	int i;

	i = c - 1;
	while (++i < lines)
	{
		arrt[i - 1] = arrt[i];
	}
}

void	middlecheck(t_arrt *arrt, int lines, int x)
{
	int i;
	int c;

	i = lines;
	c = 0;
	while (--i)
	{
		if (arrt[i].arr[arrt[i].count - 1] < x)
		{
			arrt[i].arr[arrt[i].count] = x;
			c = arrt[i].count;
			arrt[i].count++;
			break;
		}
	}
	i = lines;
	while (--i)
		if (arrt[i].count == c)
			emptyarr(arrt[i]);
	i = lines;
	while (--i)
		if (arrt[i - 1].arr[0] == 0)
			swaparr(arrt, i, lines);
}


void countBination(int *arr, int count)
{
	t_arrt *arrt;
	int i;
	int j;
	int lines;

	arrt = malloc(sizeof(t_arrt) * count);
	i = -1;
	j = 0;
	lines = 1;
	arrt[0].arr = ft_calloc(lines, sizeof(int));
	arrt[0].arr[0] = arr[0];
	while (++i < count)
	{
		if (checkrevarr(arrt, lines, arr[i]))
		{
			arrt[lines - 1].arr[arrt[lines - 1].count] = arr[i];
			arrt[lines - 1].count++;
		}
		else
		{
			middlecheck(arrt, lines, arr[i]);
			lines--;
		}
		if (i == )
	}
}

int checkintrip(int *arr, int count, int checker)
{
	int i;

	i = -1;
	while(++i < count)
		if(arr[i] == checker)
			return (1);
	return (0);
}

void ordArr(int countArr, int *arrInt)
{
	int i;
	int j;
	int  nooo_non_lo_so;

	i = 0;
    while(i < countArr)
    {
        j = i + 1;
        while(j < countArr)
        {
            if (arrInt[i] > arrInt[j])
            {
                nooo_non_lo_so = arrInt[j];
                arrInt[j] = arrInt[i];
                arrInt[i] = nooo_non_lo_so;
            }
            j++;
        }
        i++;
    }
}

int	*numerateArr(int countArr, int *temp, int *arrInt)
{
	int i;
	int j;
	int k;
	int *mamma;

	i = -1;
	j = -1;
	k = 0;
	mamma = malloc(sizeof(int) * countArr);
	ordArr(countArr, temp);
	while (++i < countArr)
	{
		j = -1;
		while (++j < countArr)
			if (temp[j] == arrInt[i] && !checkintrip(mamma, k, j + 1))
				mamma[k++] = j + 1;
	}
	return (mamma);

}


int main(int argc, char *argv[])
{
	int i;
	int *arrint;
	int *temp;
	int max;
	int *mamma;

	i = -1;
	arrint = malloc(sizeof(int) * (argc - 1));
	temp = malloc(sizeof(int) * (argc - 1));
	while (++i < argc - 1)
	{
		arrint[i] = ft_atoi(argv[i + 1]);
		temp[i] = ft_atoi(argv[i + 1]);
	}
	mamma = numerateArr(argc - 1, temp, arrint);
	countBination(mamma, argc - 1);
	for (int a = 0; a < argc - 1; a++)
		printf("%d - %d \n", mamma[a], arrint[a]);
}



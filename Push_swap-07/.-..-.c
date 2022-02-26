#include "pusciacca.h"

int findComb(int *arr, int *comb, int count, int x)
{
	int i;
	int k;
	int j;
	int c;

	i = x;
	comb = malloc(sizeof(int) * count);
	j = -1;
	k = -1;
	c = 1;
	while (++i != x)
	{
		if (arr[i] == arr[j] + 1)
		{
			comb[++k] = arr[i];
			c += 1;
			j = i;
		}
		if (i == count)
			i = -1;
	}
	i = x;
	while (++i != )
	{
		if (arr[i] == x + 1)
		{
			comb[++j] = arr[i];
			c += 1;
			x = arr[i];
		}
	}
	return (c);
}

int countBination(int *arr, int count)
{
	int i;
	int k;
	int j;
	int c;
	int max;

	i =  -1;
	max = 1;
	c = 1;
	j =  -1;
	k = i;
	while (++i < count)
	{
		c = 1;
		j = i;
		k = i;
		while (++j != i)
		{
			if (arr[j] == arr[k] + 1)
			{
				c += 1;
				k = j;
			}
			if (j == count)
				j = -1;
		}
		if (j == count - 1)
			j =  -1;
		else
			j = i;
		if (c > max)
			max = c;
	}
	return (max);
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
	max = countBination(mamma, argc - 1);
	for (int a = 0; a < argc - 1; a++)
		printf("%d - %d\n", mamma[a], max);
}



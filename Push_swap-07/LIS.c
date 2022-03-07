/* A Naive C recursive implementation
of LIS problem */
#include <stdio.h>
#include <stdlib.h>

/* To make use of recursive calls, this
function must return two things:
1) Length of LIS ending with element arr[n-1].
	We use max_ending_here for this purpose
2) Overall maximum as the LIS may end with
	an element before arr[n-1] max_ref is
	used this purpose.
The value of LIS of full array of size n
is stored in *max_ref which is our final result
*/
int _lis(int arr[], int n, int* max_ref, int *int_arr2)
{
	int	*int_arr;

	int_arr = malloc(n);
	/* Base case */
	if (n == 1)
		return 1;

	// 'max_ending_here' is length of LIS
	// ending with arr[n-1]
	int res, max_ending_here = 1, count = 0, i = 1;

	/* Recursively get all LIS ending with arr[0],
	arr[1] ... arr[n-2]. If arr[i-1] is smaller
	than arr[n-1], and max ending with arr[n-1]
	needs to be updated, then update it */
	while (i < n)
	{
		res = _lis(arr, i, max_ref, int_arr);
		if (arr[i - 1] < arr[n - 1] && res + 1 > max_ending_here)
		{
			int_arr[count++] = arr[i - 1];
			max_ending_here = res + 1;
		}
		i++;
	}

	// Compare max_ending_here with the overall
	// max. And update the overall max if needed
	if (*max_ref < max_ending_here)
	{
		for(int i = 0; i < n - 1; i++)
			int_arr2[i] = int_arr[i];
		*max_ref = max_ending_here;
	}

	// Return length of LIS ending with arr[n-1]
	return max_ending_here;
}

// The wrapper function for _lis()
int lis(int arr[], int n)
{
	int	*int_arr2;
	// The max variable holds the result
	int max = 1;

	int_arr2 = malloc(9);
	// The function _lis() stores its result in max
	_lis(arr, n, &max, int_arr2);
	for(int i = 0; i < n - 1; i++)
		printf("%d ", int_arr2[i]);
	printf("\n");

	// returns max
	return max;
}

/* Driver program to test above function */
int main()
{
	int arr[] = { 10, 22, 9, 33, 21, 50, 41, 60, 80 };
	int n = sizeof(arr) / sizeof(arr[0]);
	printf("Length of lis is %d", lis(arr, n));
	return 0;
}
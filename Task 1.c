#include <stdio.h>
#include <stdlib.h>


int main() {
	
	int row = 7, i = 1;
	
	while(i <= row)
	{
		int j = 1;
		while(j <= row)
		{
			if(j <= i)// handling the numeric incrementing value till row number
			{
				printf("%d",j); 
			}
			else// handling the star decrementing value once row number has been reached in each iteration
			{
				printf("*");
			}
			j++;
		}
		printf("\n");
		i++;
	}
	return 0;
}

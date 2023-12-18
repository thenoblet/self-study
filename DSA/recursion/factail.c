#include <stdio.h>

int facttail(int number, int result);

/*****************************************************************************
* 									     *
* ------------------------------ facttail.c ------------------------------   *
* 									     *
*****************************************************************************/

int main(void)
{
	int number;
	printf("Enter Number: ");
	scanf("%d", &number);

	//int result = facttail(number, 1);

	printf("The factorial of %d is %d\n", number, facttail(number, 1));
}


int facttail(int number, int result)
{
	if (number < 0)
		return (0);
	else if (number == 1)
		return (result);
	else if (number == 0)
		return (1);
	else
		return (facttail(number - 1, number * result));
}

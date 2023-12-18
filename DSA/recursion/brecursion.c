#include <stdio.h>

int fact(int number);

int main(void)
{
	int number;
	printf("Enter Number: ");
	scanf("%d", &number);

	//fact(number);

	printf("The factorial of %d is %d\n", number, fact(number));

}

int fact(int number)
{
	if (number < 0)
		return (0);
	else if (number == 1)
		return (1);
	else 
		return (number * fact(number - 1));
}
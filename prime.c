#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min+1; i <= max; i++)
    {
        if (prime(i) == true)
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    bool answer;
    for (int i = 2; i < number-1; i++)
    {
        if (number % i == 0) {
            answer = false;
            break;
        }
        else if (number % i !=0) {
            answer = true;
        }
    }
    return answer;
}
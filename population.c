#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start;
    do
    {
        start = get_int("Enter a start size: ");
    }
    while (start < 9);

    // TODO: Prompt for end size
    int end;
    do
    {
        end = get_int("Enter an end size: ");
    }
    while (end < start);

    // TODO: Calculate number of years until we reach threshold

    int years_passed = 0;
    int net_population;
    while (start < end)
    {
        net_population = start + start / 3 - start / 4;
        start = net_population;
        years_passed++;
    }

    // TODO: Print number of years
    printf("Years: %i\n", years_passed);
}

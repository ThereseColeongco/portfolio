#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks]; // array called hours contains as many items as # of weeks

    for (int i = 0; i < weeks; i++) // prompts for Week # HW Hours for every week. stops once it reaches the number of weeks you inputted
    {
        hours[i] = get_int("Week %i HW Hours: ", i); // stores number of hours for every week in hours array
    }

    char output;
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    while (output != 'T' && output != 'A');
    // if user didn't input T or A, keep prompting them for T or A.

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
    // print to the 10ths place, the total number of hours spent if user input T.
    // print to the 10ths place, the average number of hours spent if user input A.
}

// TODO: complete the calc_hours function
float calc_hours(int hours[], int weeks, char output)
{
    float total = 0;

    for (int i = 0; i < weeks; i++)
    {
        total += hours[i];
    }

    if (output == 'T')
    {
        return total;
    }
    else if (output == 'A')
    {
        float avg = total / weeks;
        return avg;
    }
    else
    {
        return 0;
    }
}
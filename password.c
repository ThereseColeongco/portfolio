// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    // iterate through string password. check if password[n] is lower, is upper, or is symbol.
    // number of is lower, number of is upper, number of is symbol.
    // if each number is > 0, return true;
    // else return false.
    int n = 0;
    int count_lower = 0;
    int count_upper = 0;
    int count_symbol = 0;

    while (password[n] != '\0')
    {
        if (islower(password[n]))
        {
            count_lower++;
        }
        else if (isupper(password[n]))
        {
            count_upper++;
        }
        else
        {
            count_symbol++;
        }
        n++;
    }

    if (count_lower > 0 && count_upper > 0 && count_symbol > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

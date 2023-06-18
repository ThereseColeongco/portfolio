// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>

string replace(string input);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        printf("%s\n", replace(argv[1]));
    }
    else
    {
        printf("Usage: ./novowels word\n");
        return 1;
    }
}

string replace(string input)
{
    int n = 0;
    char vowels[] = {'a', 'e', 'i', 'o'};
    char replacement[] = {'6', '3', '1', '0'};
    // we must use while loop, not for loop b/c we don't know in advance how long the string is
    while (input[n] != '\0') // iterate through each character in string called name. while character in name is not the null character (\0 is how we say "null character" in form of a character)
    {
        for (int i = 0; i < 4; i++)
        {
            if (input[n] == vowels[i])
            {
                input[n] = replacement[i];
            }
        }
        n++;
    }
    return input;
}
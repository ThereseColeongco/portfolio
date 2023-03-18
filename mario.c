#include <cs50.h>
#include <stdio.h>


int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height < 1);


    for (int i = 0; i < height; i++) // for every row
    {
        /*
        for (int k = height - 1; k > i; k--) // moves pyramid so it's right-aligned
        {
            // e.g. print 4 ., next row print 3 ., next row print 2 ., next row print 1 ., next row print 0 .
            // start at k = height - 1 then - 1 each row until k = 0
            printf(" ");
        }

        for (int j = 0; j < i + 1; j++) // add 1 # to each row, then go to new line for left-aligned pyramid
        {
            printf("#");
        }
        printf("\n");
        */
        // alternatively:
        for (int j = 0; j < height; j++) { // for every column
            if (i + j < height - 1) {
                printf(" ");
            }
            else {
                printf("#");
            }
        }
        printf("\n");
    }
}
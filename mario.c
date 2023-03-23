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

    // print 7 ., 1 #, 2 ., 1 #
    // print 6 ., 2 #, 2 ., 2 #
    // print 5 ., 3 #, 2 ., 3 #
    // and so on

    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < height + row + 3; column++)
        {
            if (row + column < height - 1 || column == height || column == height + 1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }

}
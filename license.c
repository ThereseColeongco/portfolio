#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[7];

    // Create array to store plate numbers
    char *plates[8];
    for (int i = 0; i < 8; i++)
    {
        plates[i] = malloc(sizeof(buffer));
    }
    // this works b/c you're only dealing with doubles:
        // a file of doubles that you want to put into array double* arr2 = malloc(sizeof(double) * 80);
    // doing char *plates = malloc(8 * sizeof(buffer)); will not work b/c you're putting an array of characters (buffer) into array of strings (plates)
    // doing ^^ would put 8 * 7 = 56 chars into 1 string so that's why it doesn't work.
    // https://www.reddit.com/r/cs50/comments/10i0iq6/trouble_with_week_4_practice_license/

    FILE *infile = fopen(argv[1], "r");

    int idx = 0;

    while (fread(buffer, 1, 7, infile) == 7)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // Save plate number in array
        strcpy(plates[idx], buffer);
        // buffer stores address of first character in buffer array.
        // plates[idx] is supposed to store the address of first character of string in plates array.
        // it seems that inside the while loop, buffer and plates change as they're supposed to
        // but outside the while loop, it doesn't
        // local variables.
        // to circumvent that, we need pointers...
        // cuz rn, it all goes to the same address - every element gets the same address, so each previous string is replaced by the subsequent one, so when you get OUT of the while loop, every element only has 1 address and what's stored at that address? the last string from the while loop aka the last plate number from plates.txt.
        // to ensure it doesn't all go to the same address, we need a new address from malloc. how many addresses do we want? we want 8 new addresses, 1 for each plate/element in array. and we want to store the first address we're given in a pointer variable.
        // once we have that new address, we copy the data into the pointer using strcpy
        idx++;
    }


    for (int i = 0; i < 8; i++)
    {
        printf("%s %p\n", plates[i], plates[i]);
    }
}

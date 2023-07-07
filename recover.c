#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE; // 8 bits = BYTE

// Your program should accept exactly one command-line argument, the name of a forensic image from which to recover JPEGs.
int main(int argc, char *argv[])
{
    // If your program is not executed with exactly one command-line argument, it should remind the user of correct usage, and main should return 1.
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // open memory card
    FILE *unrecovered = fopen(argv[1], "r");

    // If the forensic image cannot be opened for reading, your program should inform the user as much, and main should return 1.
    if (unrecovered == NULL)
    {
        printf("Forensic image cannot be opened for reading.\n");
        return 1;
    }

    // create array called buffer containing 512 bytes, each element being 1 byte
    BYTE buffer[512];


    // counter for number of jpegs so that we can change the jpeg name
    int num_jpegs = 0;

    // create file called recovered to store each recovered jpeg
    FILE *recovered = NULL;

    // allocate 3 char + 1 more for \0 for the jpeg name
    char *jpg_name = malloc(4);

    // if there's no actual memory address allocated, if address is 0, return 1
    if (jpg_name == NULL)
    {
        return 1;
    }

    // read card.raw (whose file pointer is stored in unrecovered) in 512 byte chunks and store each new chunk in buffer. as long as the chunk is 512 bytes...
    while (fread(buffer, 1, 512, unrecovered) == 512)
    {
        // if you find the beginning of a jpeg...
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if recovered is not null (i.e. if you DO have some stuff written into it, it's not the NULL you originally assigned it to), close the recovered file cuz ur done w/ it
            // in other words, if we find the beginning of a jpeg and that there is smth in recovered, close that file, so we can open a new one. we've finished recovering  1 jpeg.
            if (recovered != NULL)
            {
                fclose(recovered);
            }
            // otherwise (but not necessarily that recovered IS null)
            // make a new jpeg name, ++ num_jpegs every time you make a new name so each names' digits increase by 1
            sprintf(jpg_name, "%03i.jpg", num_jpegs++);

            // open a file to write in it and give it the name stored in jpg_name. store that file pointer in recovered.
            recovered = fopen(jpg_name, "w");

            // write in 512 byte chunks, the info stored in buffer into recovered, i.e. into the new jpeg
            fwrite(buffer, 1, 512, recovered);
        }
        // not all jpegs have exactly 512 bytes, so the next 512 bytes may be a continuation of the jpeg (in this case, recovered is NOT null), so continue writing.
        // since this is a loop, after checking this else if, we'd go back to the while condition, and if the while condition is true, we continue checking if we find the beginning of a jpeg
        else if (recovered != NULL)
        {
            fwrite(buffer, 1, 512, recovered);
        }
    }


    // close all remaining files

    // close the last recovered jpeg file
    if (recovered != NULL)
    {
        fclose(recovered);
    }

    // close card.raw
    fclose(unrecovered);

    // free any malloc'd memory
    free(jpg_name);
}
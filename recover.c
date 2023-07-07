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

    BYTE buffer[512];
    int num_jpegs = 0;
    FILE *recovered = NULL;
    char *jpg_name = malloc(4);

    if (jpg_name == NULL)
    {
        return 1;
    }

    while (fread(buffer, 1, 512, unrecovered) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(jpg_name, "%03i.jpg", num_jpegs++);
            recovered = fopen(jpg_name, "w");
            fwrite(buffer, 1, 512, recovered);
            fclose(recovered);
        }
    }
    fclose(unrecovered);
    free(jpg_name);
    // if ()
    // {
    //     printf("Sorry, forensic image cannot be opened for reading\n");
    //     return 1;
    // }

    // TODO: look for beginning of jpeg (0xff, 0xd8, 0xff, 0xe_smth_ at beginning)
        // assume jpegs are stored back to back

    // go to address stored in f. if that address is 0xff, go to next address, if 0xd8, go to next address, if 0xff, go to next address, if 0xe(0-f), open new jpeg file

    // TODO: open new jpeg file
    // TODO: write 512 bytes until a new jpeg is found, then close old file once 512 bytes are done.
    // keep freading in 512 byte chunks until you reach end of .raw file
}
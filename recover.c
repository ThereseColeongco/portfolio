#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE; // 8 bits = BYTE

int main(int argc, char *argv[])
{
    // goal: generate new jpeg files for each image recovered

    // TODO: open memory card
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");



    // if ()
    // {
    //     printf("Sorry, forensic image cannot be opened for reading\n");
    //     return 1;
    // }

    //fread(arr, sizeof(int), 10, ptr);
    //while( != EOF)

    // TODO: look for beginning of jpeg (0xff, 0xd8, 0xff, 0xe_smth_ at beginning)
        // assume jpegs are stored back to back

    // go to address stored in f. if that address is 0xff, go to next address, if 0xd8, go to next address, if 0xff, go to next address, if 0xe(0-f), open new jpeg file

    printf("%p", f);

    // TODO: open new jpeg file
    // TODO: write 512 bytes until a new jpeg is found, then close old file once 512 bytes are done.
    // keep freading in 512 byte chunks until you reach end of .raw file
}
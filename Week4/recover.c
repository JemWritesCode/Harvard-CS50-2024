//passes check50 cs50/problems/2024/x/recover

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCKSIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if(card == NULL)
    {
        printf("Error: Couldn't open the file. Exiting program...\n");
        return 1;
    }

    uint8_t buffer[512];
    int currentImageNum = 0;
    FILE *img = NULL;

    while(fread(buffer, 1, BLOCKSIZE, card) == 512)
    {
        //if we find the header that says this is start of JPEG
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if it's not the first jpeg we need to close the previous one first before we start writing the next one.
            if (img != NULL)
            {
                fclose(img);
            }
            char filename[8];
            sprintf(filename, "%03i.jpg", currentImageNum);
            img = fopen(filename, "w");
            fwrite(buffer, 1, BLOCKSIZE, img);
            currentImageNum++;
        }
        else
        {
            // provided we've at least found the first jpeg header
            // then we're still in the current jpeg so keep writing to it.
            if (img != NULL)
            {
                fwrite(buffer, 1, BLOCKSIZE, img);
            }
        }
    }
    fclose(card);
    fclose(img);
}

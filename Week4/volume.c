// passes check50 cs50/problems/2024/x/volume
// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Function Prototypes
void copyHeader(FILE *input, FILE *output);
void updateVolume(FILE *input, FILE *output, float factor);

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    copyHeader(input, output);
    updateVolume(input, output, factor);

    fclose(input);
    fclose(output);
}

// =============== FUNCTIONS TO IMPLEMENT
// TODO: Copy header from input file to output file
void copyHeader(FILE *input, FILE *output)
{
    // uint8_t can store 8 bits
    // make an array of these 8 bits of the header size 44.
    // Each byte of a WAV file's header can be treated as uint8_t
    uint8_t header[HEADER_SIZE];
    // fwrite's prototype is: size_t fwrite(void *ptr, size_t size, size_t nmemb, FILE *stream);
    // point to where we'll read into. the size in bytes of the type of data to read number of types to read at once
    // and the file we open
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);
}

// TODO: Read samples from input file and write updated data to output file
void updateVolume(FILE *input, FILE *output, float factor)
{
    // Make sure you use a signed int16 because sound waves can be positive or negative.
    int16_t buffer;

    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }
}

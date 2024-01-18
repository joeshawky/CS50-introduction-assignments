#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *fInput = fopen(argv[1], "r");

    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, fInput);

    // Use check_format to ensure WAV format
    // TODO #4
    if (!check_format(header))
    {
        printf("Input is not a WAV file.\n");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *fOutput = fopen(argv[2], "w");

    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, fOutput);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(header);

    // Write reversed audio to file
    // TODO #8
    BYTE data[block_size];

    int current = ftell(fInput);

    fseek(fInput, 0, SEEK_END);
    int end = ftell(fInput);

    int block_count = (end - current) / block_size;

    BYTE datas[block_count][block_size];

    for (int i = block_size; i <= block_count * block_size; i += block_size)
    {
        fseek(fInput, -i, SEEK_END);
        fread(data, block_size, 1, fInput);
        fwrite(data, block_size, 1, fOutput);
    }

    // while (fread(data, block_size, 1, fInput) == 1)
    // {
    //     memcpy(datas[data_counter], data, block_size);
    //     data_counter++;
    // }

    // for (int i = data_counter-1; i >= 0; i--)
    // {
    //     fwrite(datas[i], block_size, 1, fOutput);
    // }

    fclose(fInput);
    fclose(fOutput);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    bool isWavFormat = header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E';

    return isWavFormat;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return (header.numChannels * header.bitsPerSample) / 8;
}

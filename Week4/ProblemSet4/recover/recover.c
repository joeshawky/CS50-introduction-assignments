#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    FILE *output = NULL;
    BYTE buffer[512];
    char fileName[8] = {0};
    int jpegCount = 0;

    while (fread(buffer, sizeof(buffer), 1, file) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {
            if (output != NULL)
                fclose(output);

            sprintf(fileName, "%03d.jpg", jpegCount);
            jpegCount++;

            output = fopen(fileName, "w");
        }

        if (output != NULL)
        {
            fwrite(buffer, sizeof(buffer), 1, output);
            printf("fileName: %s\n", fileName);
        }
    }

    if (output != NULL)
        fclose(output);

    fclose(file);
    return 0;
}

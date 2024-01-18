#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);
int **string_to_bytes(string message, int char_count);
int *char_to_bits(char character);
void output_bytes(int **bytes, int char_count);

int main(void)
{
    // TODO
    string message = get_string("Message: ");
    int char_count = strlen(message);
    int **bytes = string_to_bytes(message, char_count);

    output_bytes(bytes, char_count);

    free(bytes);
}

int **string_to_bytes(string message, int char_count)
{
    int **bytes = (int **) malloc(char_count * sizeof(int *));

    for (int i = 0; i < char_count; i++)
    {
        int *bits = char_to_bits(message[i]);
        bytes[i] = bits;
    }

    return bytes;
}

int *char_to_bits(char character)
{
    int *bits = malloc(BITS_IN_BYTE * sizeof(int));
    int i = BITS_IN_BYTE - 1;

    while (character > 0)
    {
        bits[i] = character % 2;
        character /= 2;
        i--;
    }

    return bits;
}

void output_bytes(int **bytes, int char_count)
{
    for (int i = 0; i < char_count; i++)
    {
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            print_bulb(bytes[i][j]);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}

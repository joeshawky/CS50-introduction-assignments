#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    doa
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    int i;
    int j;
    int k;

    for (i = height; i > 0; i--)
    {
        for (k = i - 1; k > 0; k--)
        {
            printf(" ");
        }
        for (j = i - 1; j < height; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}

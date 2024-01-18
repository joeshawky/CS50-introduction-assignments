#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start_size;
    do
    {
        start_size = get_int("Start size: ");
    }
    while (start_size < 9);

    // TODO: Prompt for end size
    int end_size;
    do
    {
        end_size = get_int("End size: ");
    }
    while (end_size < start_size);

    // TODO: Calculate number of years until we reach threshold

    int dead_llamas;
    int newly_born_llamas;
    int current_llamas_count = start_size;
    int years = 0;
    while (current_llamas_count < end_size)
    {
        dead_llamas = current_llamas_count / 4;
        newly_born_llamas = current_llamas_count / 3;
        current_llamas_count = current_llamas_count + newly_born_llamas - dead_llamas;
        years++;
    }

    // TODO: Print number of years
    printf("Years: %d\n", years);
}

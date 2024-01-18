#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN_CARD_LENGTH 13
#define MAX_CARD_LENGTH 16

int length(long number);
bool validate_card(int *card_number, int card_length);
int *long_to_int_array(long number, int number_length);
bool is_amex(int card_length, int tenth_value);
bool is_visa(int card_length, int tenth_value);
bool is_mastercard(int card_length, int tenth_value);
char *card_type(int *number_buffer, int card_length);

int main(void)
{
    long card_number = get_long("Number: ");

    int card_length = length(card_number);

    bool card_length_valid = card_length >= MIN_CARD_LENGTH && card_length <= MAX_CARD_LENGTH;

    if (!card_length_valid)
    {
        printf("INVALID\n");
        return 0;
    }

    int *number_buffer = long_to_int_array(card_number, card_length);
    if (!validate_card(number_buffer, card_length))
    {
        printf("INVALID\n");
        return 0;
    }

    char *type = card_type(number_buffer, card_length);

    printf("%s", type);

    return 0;
}

int length(long number)
{
    int length = 0;

    do
    {
        number /= 10;
        length++;
    }
    while (number > 0);

    return length;
}

int *long_to_int_array(long number, int number_length)
{
    int *number_buffer = malloc(sizeof(int) * number_length);

    for (int i = 0; i < number_length; i++)
    {
        number_buffer[i] = number % 10;
        number /= 10;
    }

    return number_buffer;
}

bool validate_card(int *number_buffer, int card_length)
{
    int total = 0;
    int temp;
    for (int i = 0; i < card_length; i++)
    {
        if (i % 2 == 0)
        {
            total += number_buffer[i];
            continue;
        }

        temp = (2 * number_buffer[i]);

        if (temp <= 9)
        {
            total += temp;
        }
        else
        {
            total += (temp / 10);
            total += (temp % 10);
        }
    }

    return (total % 10 == 0);
}

char *card_type(int *number_buffer, int card_length)
{
    int first_number = number_buffer[card_length - 1];
    int second_number = number_buffer[card_length - 2];
    int tenth_value = first_number * 10 + second_number;

    if (is_amex(card_length, tenth_value))
    {
        return "AMEX\n";
    }
    else if (is_mastercard(card_length, tenth_value))
    {
        return "MASTERCARD\n";
    }
    else if (is_visa(card_length, first_number))
    {
        return "VISA\n";
    }

    return "INVALID\n";
}

bool is_amex(int card_length, int tenth_value)
{
    if (card_length == 15 && (tenth_value == 34 || tenth_value == 37))
    {
        return true;
    }

    return false;
}

bool is_mastercard(int card_length, int tenth_value)
{
    if (card_length == 16 && (tenth_value >= 51 && tenth_value <= 55))
    {
        return true;
    }
    return false;
}

bool is_visa(int card_length, int first_number)
{
    if ((card_length == 16 && first_number == 4) || card_length == 13)
    {
        return true;
    }

    return false;
}

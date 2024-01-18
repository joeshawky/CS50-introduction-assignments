#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool validate_arg(int argc, string argv[]);
int string_to_int(string arg);
string cipher_text(string plain_text, int key);

int main(int argc, string argv[])
{

    if (!validate_arg(argc, argv))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string plain_text = get_string("plaintext: ");

    int cipher_key = string_to_int(argv[1]) % 26;

    string ciphered_text = cipher_text(plain_text, cipher_key);

    printf("ciphertext: %s\n", ciphered_text);
}

bool validate_arg(int argc, string argv[])
{
    if (argc != 2)
    {
        return false;
    }

    int num = string_to_int(argv[1]);

    return num == -1 ? false : true;
}

int string_to_int(string arg)
{
    int total = 0;
    int length = strlen(arg);

    int constant = 1;
    int temp_length = length;
    while (temp_length > 1)
    {
        constant *= 10;
        temp_length -= 1;
    }

    for (int i = 0; i < length; i++)
    {
        if (arg[i] < '0' || arg[i] > '9')
        {
            return -1;
        }
        total += (constant * (arg[i] - '0'));
        constant /= 10;
    }

    return total;
}

string cipher_text(string plain_text, int key)
{

    int length = strlen(plain_text);
    string ciphered_text = (string) malloc(length * sizeof(char));
    bool is_letter;
    bool is_upper;
    char diff_char;
    for (int i = 0; i < length; i++)
    {
        is_letter = plain_text[i] >= 'A' && plain_text[i] <= 'z';

        if (!is_letter)
        {
            ciphered_text[i] = plain_text[i];
            continue;
        }

        is_upper = plain_text[i] >= 'A' && plain_text[i] <= 'Z';
        diff_char = is_upper ? 'A' : 'a';

        if (key + (int) plain_text[i] - diff_char > 25)
        {
            ciphered_text[i] = plain_text[i] - (26 - key);
        }
        else
        {
            ciphered_text[i] = plain_text[i] + key;
        }
    }

    return ciphered_text;
}

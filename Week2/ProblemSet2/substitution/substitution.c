#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool validate_arg(int argc, string argv[]);
string cipher_text(string plain_text, string key);

int main(int argc, string argv[])
{
    if (!validate_arg(argc, argv))
    {
        return 1;
    }
    string plain_text = get_string("plaintext: ");

    string ciphered_text = cipher_text(plain_text, argv[1]);

    printf("ciphertext: %s\n", ciphered_text);
}

bool validate_arg(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return false;
    }

    string key = argv[1];

    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    int i = 0;
    bool is_letter;
    while (key[i] != '\0')
    {
        is_letter = key[i] >= 'A' && key[i] <= 'z';
        if (!is_letter)
        {
            return false;
        }

        i++;
    }

    return true;
}

string cipher_text(string plain_text, string key)
{
    int i = 0;
    string ciphered_text = malloc(strlen(plain_text) * sizeof(char));
    bool is_letter;
    bool is_upper;
    char char_diff;
    int char_index;

    while (plain_text[i] != '\0')
    {
        is_letter = plain_text[i] >= 'A' && plain_text[i] <= 'z';
        is_upper = plain_text[i] >= 'A' && plain_text[i] <= 'Z';
        char_diff = is_upper ? 'A' : 'a';
        char_index = (int) plain_text[i] - char_diff;

        if (is_letter)
        {
            ciphered_text[i] = is_upper ? toupper(key[char_index]) : tolower(key[char_index]);
        }
        else
        {
            ciphered_text[i] = plain_text[i];
        }

        i++;
    }

    return ciphered_text;
}

// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>

string replace(string word);

int main(int argc, string argv[])
{
    if (argc == 1 || argc > 2)
    {
        printf("ERROR");
        return 1;
    }

    string output = replace(argv[1]);
    printf("%s\n", output);


}

string replace(string word)
{
    int i = 0;
    while (word[i] != '\0')
    {
        if (word[i] == 'a')
        {
            word[i] = '6';
        }
        else if (word[i] == 'e')
        {
            word[i] = '3';
        }
        else if (word[i] == 'i')
        {
            word[i] = '1';
        }
        else if (word[i] == 'o')
        {
            word[i] = '0';
        }
        i++;
    }

    return word;
}

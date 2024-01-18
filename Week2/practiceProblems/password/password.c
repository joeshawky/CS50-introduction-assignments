// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool contains_uppercase = false;
    bool contains_lowercase = false;
    bool contains_number = false;
    bool contains_symbol = false;

    int i = 0;
    while (password[i] != '\0')
    {
        if (password[i] >= 'A' && password[i] <= 'Z')
        {
            contains_uppercase = true;
        }
        else if (password[i] >= 'a' && password[i] <= 'z')
        {
            contains_lowercase = true;
        }
        else if (password[i] >= '0' && password[i] <= '9')
        {
            contains_number = true;
        }
        else if (password[i] >= '!' && password[i] <= '/')
        {
            contains_symbol = true;
        }
        i++;
    }

    return contains_lowercase && contains_uppercase && contains_number && contains_symbol;
}

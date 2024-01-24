#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int calculate_grade(int lettersCount, int wordsCount, int sentencesCount);

int main(void)
{
    string text = get_string("Text:");
    int lettersCount = count_letters(text);
    int wordsCount = count_words(text);
    int sentencesCount = count_sentences(text);

    int grade = calculate_grade(lettersCount, wordsCount, sentencesCount);

    // printf("lettersCount: %d, wordsCount: %d, sentencesCount: %d\n", lettersCount, wordsCount, sentencesCount);

    if (grade > 16)
        printf("Grade 16+\n");
    else if (grade > 1 && grade < 17)
        printf("Grade %d\n", grade);
    else
        printf("Before Grade 1\n");
}

int count_letters(string text)
{
    int lettersCount = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char letter = tolower(text[i]);
        if (letter >= 'a' && letter <= 'z')
        {
            lettersCount += 1;
        }
    }
    return lettersCount;
}
int count_words(string text)
{
    int wordsCount = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char letter = tolower(text[i]);
        if (letter == ' ')
        {
            wordsCount += 1;
        }
    }
    return wordsCount;
}
int count_sentences(string text)
{
    int sentencesCount = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char letter = tolower(text[i]);
        if (letter == '.' || letter == '?' || letter == '!')
        {
            sentencesCount += 1;
        }
    }
    return sentencesCount;
}
int calculate_grade(int lettersCount, int wordsCount, int sentencesCount)
{
    return round(0.0588 * ((float) lettersCount / wordsCount * 100) - 0.296 * ((float) sentencesCount / wordsCount * 100) - 15.8);
}

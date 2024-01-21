// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int word_hash = hash(word);
    if (table[word_hash] == NULL)
        return false;

    node *cursor = table[word_hash];
    size_t i;
    size_t word_length = strlen(word);

    bool same_word = true;

    while (cursor)
    {
        if (strlen(word) != strlen(cursor->word))
        {
            cursor = cursor->next;
            continue;
        }

        same_word = true;
        for (i = 0, word_length = strlen(word); i < word_length; i++)
        {
            if (tolower(cursor->word[i]) != tolower(word[i]))
            {
                same_word = false;
                break;
            }
        }

        if (same_word)
            return true;

        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int i = 0;
    int total_ascii = 0;
    while (word[i] != '\0' && word[i] != '\n')
    {
        total_ascii += tolower(word[i]);
        i++;
    }
    return total_ascii % 1000;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");
    char dict_word[LENGTH];
    int hash_key;
    node *new_node = NULL;
    while (fgets(dict_word, LENGTH + 2, dict))
    {
        dict_word[strcspn(dict_word, "\n")] = 0;
        hash_key = hash(dict_word);
        new_node = malloc(sizeof(node));
        strcpy(new_node->word, dict_word);
        new_node->next = table[hash_key] ? table[hash_key] : NULL;
        table[hash_key] = new_node;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    int total_size = 0;
    node *cursor = NULL;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            total_size++;
            cursor = cursor->next;
        }
    }
    return total_size;
}

void unloader(node *current)
{
    if (current == NULL)
    {
        return;
    }
    if (current->next == NULL)
    {
        free(current);
        return;
    }

    unloader(current->next);

    free(current);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        unloader(table[i]);
    }
    return true;
}

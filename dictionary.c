// Implements a dictionary's functionality
#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
// dictionaries contain lists of correctly spelled words.
// texts contain sample texts to run spell checker against
// keys contain lists of mispelled words in each sample text.

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26 * 26 * 26 * 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
    // iterate through linked list using a "cursor" and look for the word, making sure to strcasecmp each word in the list
    // if word is in linked list, return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // reference: https://www.reddit.com/r/cs50/comments/w4tqyf/looking_for_advice_on_my_hash_function_for_speller/

    int hash = 0;
    int last_char = strlen(word);
    if (word[last_char] == '\0' || word[last_char] == '\n')
    {
        for (int i = 0; i < last_char; i++)
        {
            int function = toupper(word[i]) - 'A';
            hash += (function * ((i + 1) * 11)) % N;
        }
        return hash;
    }
    return hash;
}

// Loads all words in dictionary into memory (hash table), returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open dictionary file
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    // read strings from file one at a time
    while (fscanf(file, "%s", word) != EOF)
    {
        // create new node for each string (word)
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        int index = hash(strcpy(n->word, word));
        if (table[index] != NULL)
        {
            n->next = table[index];
            table[index] = n;
        }
        else
        {
            table[index] = n;
            n->next = NULL;
        }
    }
    fclose(file);
    // false if memory error or file opening error
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    node *ptr = NULL;
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        ptr = table[i];
        // if table[i] is NULL, ptr->next doesn't exist, so need to check if ptr != NULL. if it is NULL, go to next index
        if (ptr != NULL)
        {
            count++;
            while (ptr->next != NULL)
            {
                count++;
                ptr = ptr->next;
            }
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // iterate over each linked list in hash table, free each node

    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp = NULL;
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
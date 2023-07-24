// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// ideally, O(n/k) where k = number of buckets for a hash table
// the greater k is, the faster the running time IRL
// this means evenly distributed data across the buckets... there's no unused buckets but it's fast bc the list of stuff inside a bucket is relatively short
// faster if u don't care if data is sorted

// dictionaries contain lists of correctly spelled words.
// texts contain sample texts to run spell checker against
// keys contain lists of mispelled words in each sample text.



// hash - take a word and run a hash function on it. return a number. that number is the index of the array element pointing to the linked list that the word will go in.
    // each node contains char word[LENGTH + 1] and struct node *next (pointer to the next word in the list)
    // last *next = NULL;
// size - how many words in dictionary
// check - is word in dictionary or not? (i.e. is it correctly spelled?)
// unload - any memory allocated to store data in data structure is freed

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
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

        // when ur at the part where you're gonna add a new node to an existing linked list,
        // draw out the linked list and pointers to order them correctly
    }

    // store dictionary in hash table by calling hash() to obtain a hash value for each word
        // w/c linked list to put in? hash function.
        // add more data to hash table: use node *n = malloc(sizeof(node)); and smth like strcpy(n->word, "Hello"); w/c copies "Hello" into n->word
    // insert node into hash table at that location
    // return true if successful (dictionary stored)

    // false if memory error or file opening error
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}

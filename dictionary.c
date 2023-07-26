// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
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
    }
    fclose(file);
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
    // either iterate over every linked list in hash table and count # of nodes in each
    // or as you're loading hash table, keep track of number of words you're adding to dictionary so far so you can return that value in size function
    // the "as you're loading option" may be faster? how can we know when a new item has been added to hash table?
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
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

// letter = any lowercase or uppercase character from A to Z
// word = any sequence of characters separated by spaces
// sentence = any occurrence of a ., !, or ? is end of sentence

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");

    // L = average number of letters / 100 words
    float L = ((float) count_letters(text) / count_words(text)) * 100;

    // S = average number of sentences per 100 words
    float S = ((float) count_sentences(text) / count_words(text)) * 100;

    // Coleman-Liau index
    float index = (0.0588 * L) - (0.296 * S) - 15.8;

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}

int count_letters(string text)
{
    int count_letter = 0;
    int n = 0;

    while (text[n] != '\0')
    {
        if (isalpha(text[n]))
        {
            count_letter++;
        }
        else
        {
            count_letter += 0;
        }
        n++;
    }
    return count_letter;
}

int count_words(string text)
{
    int count_words = 0;
    int n = 0;

    while (text[n] != '\0')
    {
        if (text[n] == ' ')
        {
            count_words++;
        }
        n++;
    }
    count_words++;
    return count_words;
}

int count_sentences(string text)
{
    int count_sentences = 0;
    int n = 0;

    while (text[n] != '\0')
    {
        if (text[n] == '.' || text[n] == '?' || text[n] == '!')
        {
            count_sentences++;
        }
        n++;
    }
    return count_sentences;
}
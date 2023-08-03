#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

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

    // reports grade level of text to nearest whole number
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

    // iterates through text. for every character in text, if character is a letter in the alphabet, add 1 to letter counter. if character is not a letter in the alphabet, add 0 to letter counter.
    while (text[n] != '\0')
    {
        if (isalpha(text[n]))
        {
            count_letter++;
        }
        n++;
    }

    return count_letter;
}

int count_words(string text)
{
    int count_words = 0;
    int n = 0;

    // iterates through text. for every character in text, if character is a space, that means we've just passed a word, so add 1 to word counter.
    while (text[n] != '\0')
    {
        if (text[n] == ' ')
        {
            count_words++;
        }
        n++;
    }

    // add 1 extra to word counter b/c at the end of the text, there's 1 more word but no space to indicate a word.
    count_words++;

    return count_words;
}

int count_sentences(string text)
{
    int count_sentences = 0;
    int n = 0;

    // iterates through text. for every character in text, check if the character is a ., ?, or !. if it's any of those, add 1 to sentence counter.
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
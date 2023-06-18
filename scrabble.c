#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int n = 0;
    int score = 0;
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // iterate through string word.
    while (word[n] != '\0')
    {
        // if char in word is upper or is lower,
        if (isupper(word[n]) || islower(word[n]))
        {
            // iterate through string alpha and through POINTS array.
            for (int i = 0; i < 26; i++)
            {
                // change char in word to uppercase and if that char is the current char in alpha,
                if (toupper(word[n]) == alpha[i])
                {
                    // add points corresponding to char in alpha to score.
                    score += POINTS[i];
                }
            }
        }
        else
        {
            // if char in word is not a letter, add 0 to score.
            score += 0;
            // e.g. if user types Oh, it should only count points for O and h, not the comma.
        }
        n++;
    }
    return score;
}

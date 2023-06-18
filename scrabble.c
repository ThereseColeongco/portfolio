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
    // e.g. string Oh,
    while (word[n] != '\0')
    {
        if (isupper(word[n]) || islower(word[n]))
        {
            for (int i = 0; i < 26; i++)
            {
                if (toupper(word[n]) == alpha[i])
                {
                    score += POINTS[i];
                    // i is incrementing but no points are being added. score = 0 always.
                }
            }
        }
        else
        {
            score += 0;
            // e.g. if user types Oh, it should only count points for O and h, not the comma.
        }
        n++;
    }
    return score;
    // iterate through string word.
    // if not isupper or not islower, 0 points
    // else, iterate through string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        // if word[n] == alpha[i], iterate through points array.
            // int score += points[i]
}

#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// each of our text files contains 1000 words
#define LISTSIZE 1000

// values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// ANSI color codes for boxed in letters
#define GREEN   "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW  "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED     "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET   "\e[0;39m"

// user-defined function prototypes
string get_guess(int wordsize);
int check_word(string guess, int wordsize, int status[], string choice);
void print_word(string guess, int wordsize, int status[]);

int main(int argc, string argv[])
{
    // ensure proper usage
    // TODO #1
    if (argc != 2)
    {
        printf("Usage: ./wordle wordsize\n");
        return 1;
    }

    int wordsize = 0;

    // ensure argv[1] is either 5, 6, 7, or 8 and store that value in wordsize instead
    // TODO #2
    // atoi() = argument to integer; converts string to integer
    if (atoi(argv[1]) == 5 || atoi(argv[1]) == 6 || atoi(argv[1]) == 7 || atoi(argv[1]) == 8)
    {
        wordsize = atoi(argv[1]);
    }
    else
    {
        printf("Error: wordsize must be either 5, 6, 7, or 8\n");
        return 1;
    }

    // open correct file, each file has exactly LISTSIZE words
    char wl_filename[6];
    sprintf(wl_filename, "%i.txt", wordsize);
    FILE *wordlist = fopen(wl_filename, "r");
    if (wordlist == NULL)
    {
        printf("Error opening file %s.\n", wl_filename);
        return 1;
    }

    // load word file into an array of size LISTSIZE
    char options[LISTSIZE][wordsize + 1];

    for (int i = 0; i < LISTSIZE; i++)
    {
        fscanf(wordlist, "%s", options[i]);
    }

    // pseudorandomly select a word for this game
    srand(time(NULL));
    string choice = options[rand() % LISTSIZE];

    // allow one more guess than the length of the word
    int guesses = wordsize + 1;
    bool won = false;

    // print greeting, using ANSI color codes to demonstrate
    printf(GREEN"This is WORDLE50"RESET"\n");
    printf("You have %i tries to guess the %i-letter word I'm thinking of\n", guesses, wordsize);

    // main game loop, one iteration for each guess
    for (int i = 0; i < guesses; i++)
    {
        // obtain user's guess
        string guess = get_guess(wordsize);

        // array to hold guess status, initially set to zero
        int status[wordsize];

        // set all elements of status array initially to 0, aka WRONG
        // TODO #4
        for (int j = 0; j < wordsize; j++)
        {
            status[j] = WRONG;
        }

        // Calculate score for the guess
        int score = check_word(guess, wordsize, status, choice);
        printf("%i\n", score);

        printf("Guess %i: ", i + 1);

        // Print the guess
        print_word(guess, wordsize, status);

        // if they guessed it exactly right, set terminate loop
        if (score == EXACT * wordsize)
        {
            won = true;
            break;
        }
    }

    // Print the game's result
    // TODO #7
    if (won == true)
    {
        printf("You won!\n");
    }
    else
    {
        printf("%s\n", choice);
    }

    // that's all folks!
    return 0;
}

string get_guess(int wordsize)
{
    string guess = "";

    // ensure users actually provide a guess that is the correct length
    // TODO #3
    do
    {
        guess = get_string("Input a %i-letter word: ", wordsize);
    }
    while (strlen(guess) < wordsize || strlen(guess) > wordsize);

    return guess;
}

int check_word(string guess, int wordsize, int status[], string choice)
{
    int score = 0;

    // compare guess to choice and score points as appropriate, storing points in status
    // TODO #5

    // HINTS
    // iterate over each letter of the guess
        // iterate over each letter of the choice
            // compare the current guess letter to the current choice letter
                // if they're the same position in the word, score EXACT points (green) and break so you don't compare that letter further
                // if it's in the word, but not the right spot, score CLOSE point (yellow)
        // keep track of the total score by adding each individual letter's score from above
    // wordsize of guess and of choice are the same, so you can use the same position variable. if guess[i] == choice[i], status is EXACT.
    // for a single character in guess, check if it == any character in choice. you want the iterator in choice to ++ but the iterator in guess to stay static. to check if status is CLOSE.

    int i = 0; // guess
    int j = 0; // choice

    // for each character in guess
    while (i < wordsize)
    {
        // check if character in guess is in the exact correct position of choice.
        // if it is, store EXACT = 2 in that element in status, add that element in status to score, and break loop. we're done with that character. move onto the next character.
        if (guess[i] == choice[i])
        {
            status[i] = EXACT;
            score += status[i];
            // break;
            // instructions say that if EXACT, then break out of the loop b/c we're done with that character. move onto the next character.
            // but when i break out of the loop, it no longer checks subsequent characters.

            // now i removed the break, and strangely, it doesn't go through the j while loop for the second character in guess when it finds that a in games (guess) is not e in tears (choice)???, just goes straight to i++
            // wtf is happening.
            // guess brush, choice burns: r in brush is yellowed, u in brush is red, s in brush is red. it doesn't yellow any more subsequent characters once it finds the first yellow character because j doesn't reset to 0!!!
        }
        // if character in guess is NOT in the exact correct position of choice,
        // check if character in guess is in choice word. if it is, store CLOSE = 1 in that element in status, add that element in status to score.
        else
        {
            while (j < wordsize)
            {
                if (guess[i] == choice[j])
                {
                    status[i] = CLOSE;
                    score += status[i];
                }
                j++;
            }
            j = 0;
        }
        i++;
    }

    // return total score at the end.
    return score;
}

void print_word(string guess, int wordsize, int status[])
{
    // print word character-for-character with correct color coding, then reset terminal font to normal
    // TODO #6

    // iterate through status array
    // status[i] corresponds to guess[i]
    for (int i = 0; i < wordsize; i++)
    {
        if (status[i] == 2)
        {
            printf(GREEN"%c", guess[i]);
        }
        else if (status[i] == 1)
        {
            printf(YELLOW"%c", guess[i]);
        }
        else
        {
            printf(RED"%c", guess[i]);
        }
    }
    printf(RESET"\n");
    return;
}

// trouble with the yellow: it's not consistently printing yellow when there should be...
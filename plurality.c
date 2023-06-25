#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcasecmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    // there are at most 9 candidates, so at most, each candidate gets 1 vote → tie.
    // you want to iterate through the votes for each candidate
    // check if...

// count only number of votes first. iterate through the votes array and check for a max. printf(name at that max votes index); else if max == array[i], printf(all names associated with that number of votes);
// why exactly does else if ^^ not work for all cases again? in some situations,
// when i = 0, candidates[i].votes = candidates[0].votes, which is == max.
// so the if doesn't run, only the else if runs.
// but ^^ wasn't printing only Bob when Bob is sole winner or only Charlie when Charlie is sole winner.
//
    int max = candidates[0].votes;
    string winner[MAX];
    int win_index = 0;
    for (int i = 0; i < sizeof(candidates) / sizeof(candidates[0]); i++)
    {
        //for (int j = 0; j < MAX; j++)
        //{
            if (candidates[i].votes > max)
            {
                max = candidates[i].votes;
                //winner[j] = candidates[i].name;
                printf("%s\n", candidates[i].name);
            }
            else if (max == candidates[i].votes)
            {
                //winner[j] = candidates[i].name;
                printf("%s\n", candidates[i].name);
            }
        //}
    }
    //printf("%s\n", winner[]);
}
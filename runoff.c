#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote (every rank), unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO: iterate through candidates struct. if given name is in struct, store candidate index in preferences.
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            //printf("%i\n", preferences[voter][rank]);
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
// look at all of the voters’ preferences and compute the current vote
// totals, by looking at each voter’s top choice candidate who hasn’t yet been eliminated
void tabulate(void)
{
    // TODO

    // this part is like how we counted that there are 3 votes for Bob as Rank 1, 2 votes for Alice as Rank 1, and 4 votes for Charlie as Rank 1.
    // and then how we then added the 2 who had Bob as Rank 2 to total votes for Bob b/c those 2 had Alice as Rank 1 and Alice was eliminated.
    // you don't need to account for elimination b/c eliminate function takes care of that. and in main, tabulate is run after every elimination.

    // 1st, look only at rank 1 for all voters. Count the rank 1 votes. so iterate through voters i and keep rank j the same.
    // then iterate through election candidates again to check if preferred candidate is eliminated.
    // if eliminated, j++; for those voter(s) i
    // for those voters i at a new rank j, count their new rank j votes.
    // iterate through election candidates again to add those votes? what about the vote reset in main? does that affect this?

    for (int i = 0; i < voter_count; i++)
    {
        int x = candidates[0].votes;
        for (int j = 0; j < candidate_count; j++)
        {
            if (candidates[preferences[i][j]].eliminated == false)
            {
                candidates[preferences[i][j]].votes++;
                x = candidates[preferences[i][j]].votes;
                break;
            }
        }
    }

    // int j = 0;
    // while (j < candidate_count)
    // {
    //     int x = candidates[0].votes;
    //     for (int i = 0; i < voter_count; i++) // iterating through voters in preferences array
    //     {
    //         if (candidates[preferences[i][j]].eliminated == false)
    //         {
    //             candidates[preferences[i][j]].votes++;
    //             x = candidates[preferences[i][j]].votes;
    //         }
    //         else
    //         {
    //             j++;
    //         }
    //     }
    // }


        // int j = 0;
        // while (j < candidate_count)
        // {
        //     candidates[preferences]

        //     if (candidates[j].eliminated == false)
        //     {
        //         candidates[preferences[i][j]].votes++;
        //         x = candidates[preferences[i][j]].votes;
        //         j++;
        //     }

            /*
            if (candidates[j].eliminated == true)
            {
                j++;
                candidates[preferences[i][j]].votes++;
                x = candidates[preferences[i][j]].votes;
            }
            else
            {
                candidates[preferences[i][j]].votes++;
                x = candidates[preferences[i][j]].votes;
                j++;
            }
            */
    //     }
    // }

    //     for (int j = 0; j < candidate_count; j++) // iterating through ranks in preferences array
    //     {}

    // preferences[voter][rank]
    // is
    // for every voter i, iterate through rank j and candidates struct
        // if candidate[c].eliminated == true
            // j++;
        // else
            // candidates[c].votes++; where c = index in candidates struct in preferences aka
    //
    // int preferences[MAX_VOTERS][MAX_CANDIDATES];
    // The array preferences[i] will represent all of the preferences for voter number i, and the integer preferences[i][j] here will store the index of the candidate
    // who is the jth preference for voter i.
    // so how do i use this preferences array?
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > (voter_count / 2))
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int min = voter_count;
    // iterate through candidates struct (i < candidate_count)
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes <= min && candidates[i].eliminated == false)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    // min tells us which candidates should be eliminated and therefore should not count in the is_tie!!!!
    for (int i = 0; i < candidate_count - 1; i++)
    {
        if (candidates[i].votes == candidates[i + 1].votes && candidates[i].votes == min && candidates[i].eliminated == false)
        {
            return true;
        }
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}

/*
if any 1 candidate has >50% of first preference votes (Rank 1),
    the candidate that has >50% of first preference votes (Rank 1) is the winner.
else (if no candidate has >50% of the vote),
    the candidate who received the fewest # of votes is dropped
    anyone who originally chose that candidate as their Rank 1 now has their Rank 2 considered.
repeat the process until a single candidate has the majority:
    if none of the remaining candidates has >50% of the votes,
        the candidate who received the least votes is dropped and anyone who voted for them will now have their subsequent ranking candidate considered.
        (so basically, put the ^^ if/else into a loop)

for this problem, assume all voters rank all candidates running in election in order of preference.
if there's a tie for who has the least number of votes, all candidates who are tied for the least number of votes will be dropped unless every remaining candidate has the exact same number of votes (b/c eliminating the tied last place candidates would eliminate everyone).
when every remaining candidate has the exact same number of votes, declare the election a tie b/t all remaining candidates.
*/
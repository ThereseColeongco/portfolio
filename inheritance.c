// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
// each parent is a pointer to another person struct (i.e. each parent stores address of a node containing a 2-parent array and 2-allele array)
// each allele is a char ('A', 'B', or 'O', as defined by random_allele function)
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

// max number of generations
const int GENERATIONS = 3;

// ...
const int INDENT_LENGTH = 4;

// function prototypes

person *create_family(int generations);
// returns a pointer to a person struct

void print_family(person *p, int generation);
void free_family(person *p);

char random_allele();
// returns a character: either 'A', 'B', or 'O'


int main(void)
{
    // Seed random number generator
    // used to generate random alleles
    srand(time(0));

    // Create a new family with three generations
    // creates person structs for a family of 3 generations (a person, their parents, and their parents' parents)
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    // print out each of those family members and their blood types
    print_family(p, 0);

    // Free memory
    // free any malloc'd memory
    // what memory did you malloc? whatever was in create_family(GENERATIONS);
    // b/c you put that result which is a pointer into the pointer variable p
    free_family(p);
}

// Create a new individual with `generations`
// takes an integer generations as input and uses malloc to allocate 1 person for each member of the family of that number of generations
// returns a pointer to the person in the youngest generation
person *create_family(int generations)
{
    // TODO: Allocate memory for new person
    person *new = malloc(sizeof(person));

    // If there are still generations left to create
    if (generations > 1)
    {
        // Create two new parents for current person by recursively calling create_family
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // TODO: Set parent pointers for current person
        new->parents[0] = parent0;
        new->parents[1] = parent1;

        // TODO: Randomly assign current person's alleles based on the alleles of their parents
        // a = index of an allele in char alleles[2];
        int a = rand() % 2;
        int b = rand() % 2;
        new->alleles[0] = new->parents[0]->alleles[a];
        new->alleles[1] = new->parents[1]->alleles[b];
    }

    // If there are no generations left to create
    else
    {
        // TODO: Set parent pointers to NULL
        new->parents[0] = NULL;
        new->parents[1] = NULL;

        // TODO: Randomly assign alleles
        random_allele();
    }

    // TODO: Return newly created person
    return new;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // TODO: Handle base case
    if (p == NULL)
    {
        return;
    }
    else
    {
        // TODO: Free parents recursively
        free_family(p->parents[0]);
        free_family(p->parents[1]);

        // TODO: Free child
        free_family(p);
    }


}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    // Print parents of current generation
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}

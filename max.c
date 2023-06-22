// Practice writing a function to find a max value

#include <cs50.h>
#include <stdio.h>

int max(int array[], int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Number of elements: ");
    }
    while (n < 1);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = get_int("Element %i: ", i);
    }

    printf("The max value is %i.\n", max(arr, n));
}

// TODO: return the max value
int max(int array[], int n)
{
    int max = array[0];
    for (int i = 0; i < n; i++)
    {
        if (array[i] > array[0])
        {
            max = array[i];
        }
    }
    return max;
}



//0, 1, 3
    // when 3 is array[i], there is no array[i + 1] to compare to
//-10, -50, -100
    // when -50 is array[i], it IS greater than -100 aka array[i + 1]
    // when -100 is array[i], there's no array[i + 1] to compare to
// solution: change the sign to array[i - 1]
// problem with solution: when i = 0, aren't i accessing smth that's not in the array (i.e. array[-1])?
// solution: just compare every other element in array to 
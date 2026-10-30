#include <stdio.h>
#include <stdlib.h>

double  compute_disorder(int *tab, int size)
{
    int i = 0;
    int j;
    long inversions = 0;
    double pairs = 0;
    if(size < 2)
        return 0;
    while(i < size)
    {
        j = i + 1;
        while(j < size)
        {
            if(tab[i] > tab[j])
                inversions++;
            j++;
        }
        i++;
    }
    pairs = (double)size * (size - 1) / 2;
    return (inversions / pairs); 
}
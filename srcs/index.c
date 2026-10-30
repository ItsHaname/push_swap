#include <stdlib.h>
#include <stdio.h>
int     *index_values(int *tab, int size)
{
    int i;
    int j;
    int count;
    i = 0;
    int *index = malloc((size)*sizeof(int));
    if(!index)
        return NULL;
    while(i < size)
    {
        count = 0;
        j = 0;
        while(j < size)
        {
            if(tab[j] < tab[i])
                count++;
            j++;
        }
        index[i] = count;
        i++;
    }
    return index;
}
// int main(void)
// {
//         int tab[] = {2, 1, 0};
//         int *idx = index_values(tab, 3);
//         int i = 0;
//         while(i < 3)
//         {
//             printf("%d",idx[i]);
//             i++;
//         }
//         free(idx);
// }
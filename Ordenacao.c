#include <stdio.h>
#include <stdlib.h>

void insertion_short(int v[],int tam){
    for (int j = 2; j < tam; j++)
    {
        int chave = v[j];
        int i = j-1;
        while (i>0 && v[i]>chave)
        {
            v[i+1] = v[i];
            i = i-1;
        }
        v[i+1] = chave;
    }
}

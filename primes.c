// primes.c
// Řešení IJC-DU1, příklad a), 22.3.2022
// Autor: Jakub Kontrík, FIT
// Přeloženo: gcc 11.2
/*Vypisovanie prvocisiel vzostupne - prechod bitsetu odzadu a 
zapisovanie indexov do bufferu a nasledne vypisanie bufferu odzadu*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "bitset.h"
#include "eratosthenes.h"
#include "error.h"
int main(){
    clock_t start = clock();
    bitset_create(bit_array,300000000);
    Eratosthenes(bit_array);
    int count = 0;
    //buffer na 10 poslednych prvocisiel
    bitset_index_t num_buffer[10] = {0};
    for(bitset_index_t i = bit_array[0]-1; i >= 2;i--) {
        if(!bitset_getbit(bit_array,i)) {
            num_buffer[count] = i;
            count++;
                
        }
        if (count == 10) break;
    }
    // vypis prvocisel z bufferu vzostupne
    for(int i = 9; i >= 0; i--) {
        if(num_buffer[i] !=0 && num_buffer[i]!=1) {
            printf("%lu\n", num_buffer[i]);
        }
    }
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    return 0;
}

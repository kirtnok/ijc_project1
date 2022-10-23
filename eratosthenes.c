// eratostenes.c
// Řešení IJC-DU1, příklad a), 22.3.2022
// Autor: Jakub Kontrík, FIT
// Přeloženo: gcc 11.2
// Algoritmus eratostenovo sito
#include <math.h>
#include "eratosthenes.h"
#include "bitset.h"
void Eratosthenes(bitset_t pole){
    // nastavenie prvych 2 bitov na 1 -> 0,1 nie su prvocisla
    pole[1] = 3 << 0;
    bitset_index_t i = 2;
    while(i<sqrt(pole[0])) {
        if(!bitset_getbit(pole, i)) {
            for(bitset_index_t n = 2;(i*n)<pole[0]; n++) {
                bitset_setbit(pole,(n*i), 1);
            }
        }
        i++;
    }
}
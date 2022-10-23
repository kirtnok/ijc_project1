// bitset.h
// Řešení IJC-DU1, příklad a), 22.3.2022
// Autor: Jakub Kontrík, FIT
// Přeloženo: gcc 11.2
/* Hlavickovy subor s makrami popripade inline funkciami na deklaraciu a pracovanie s bitovymi polami. 
Pre bitset_create a bitset_alloc nebolo mozne 
vytvorit inline funkciu tak pouzivam makro pre obe moznosti*/
#ifndef BITSET_H
#define BITSET_H
#include <assert.h>
#include <stdlib.h>
#include "error.h"

typedef unsigned long *bitset_t;
typedef unsigned long bitset_index_t;
// Pocet bitov v unsigned long castopouzivane cislo preto som to nahradil makrom
#define ULONG_BITS (sizeof(bitset_index_t) * __CHAR_BIT__)
/*Pri vytvarani pola overujem delitelnost daneho cisla pre pripadnu alokaciu 
navyse ale zaroven aby sa nealokovalo zbytocne vela + 1 miesto navyse vzdy kvoli ukladaniu velkosti*/
#define bitset_create(jmeno_pole, velikost)\
    static_assert(velikost > 0, "Array allocation defined only for positive values!\n");\
    bitset_index_t jmeno_pole[(((velikost % ULONG_BITS != 0) ?\
    (velikost / ULONG_BITS + 2) : (velikost / ULONG_BITS + 1)))] = {velikost}

#define bitset_alloc(jmeno_pole, velikost)\
    assert(velikost > 0 && "Array allocation defined only for positive values!\n");\
    bitset_t jmeno_pole = (bitset_t)calloc(((velikost % ULONG_BITS != 0) ?\
    (velikost / ULONG_BITS + 2) : (velikost / ULONG_BITS + 1)), sizeof(bitset_index_t));\
    (jmeno_pole == NULL) ? error_exit("bitset_alloc: Chyba alokace paměti"),1 : (jmeno_pole[0]=velikost)

//Podmieneny preklad ak je definovane USE_INLINE tak sa prekladaju inline funkcie miesto makier
#ifdef USE_INLINE
inline void bitset_free(bitset_t jmeno_pole){
    free(jmeno_pole);
}
inline bitset_index_t bitset_size(bitset_t jmeno_pole){
    return jmeno_pole[0];
}
inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, int vyraz){
    if(index >= jmeno_pole[0]) {
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",(unsigned long)index, (unsigned long)jmeno_pole[0]-1);
    }
    bitset_index_t mask_index = index % ULONG_BITS;
    bitset_index_t mask = 1UL << mask_index;
    if(vyraz) {
        jmeno_pole[(index / ULONG_BITS)+1] |= mask;
    }
    else {
        jmeno_pole[(index / ULONG_BITS)+1] &= ~mask;
    }
}
inline bitset_index_t bitset_getbit(bitset_t jmeno_pole, bitset_index_t index) {
    if(index >= jmeno_pole[0]) {
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",(unsigned long)index, (unsigned long)jmeno_pole[0]-1);
    }
    return (jmeno_pole[(index / ULONG_BITS)+1] >> index % ULONG_BITS) & 1UL;
}
#else
#define bitset_free(jmeno_pole) free(jmeno_pole)
#define bitset_size(jmeno_pole) jmeno_pole[0]
#define bitset_setbit(jmeno_pole, index, vyraz)do{\
    if((bitset_index_t)index >= jmeno_pole[0]){\
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",(unsigned long)index, (unsigned long)jmeno_pole[0]-1);\
    }\
    bitset_index_t mask_index = index % ULONG_BITS;\
    bitset_index_t mask = 1UL << mask_index;\
    if(vyraz) {\
        jmeno_pole[(index / ULONG_BITS)+1] |= mask;\
    }\
    else {\
        jmeno_pole[(index / ULONG_BITS)+1] &= ~mask;\
    }\
}while(0)
#define bitset_getbit(jmeno_pole, index)\
    (((bitset_index_t)index >= jmeno_pole[0])? \
    error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",(unsigned long)index, (unsigned long)jmeno_pole[0]-1),1 :\
    (((jmeno_pole[(index / ULONG_BITS)+1] >> index % ULONG_BITS) & 1UL)))

#endif
#endif /* BITSET_H */
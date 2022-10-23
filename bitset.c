// bitset.c
// Řešení IJC-DU1, příklad a), 22.3.2022
// Autor: Jakub Kontrík, FIT
// Přeloženo: gcc 11.2
// Modul potrebny na spravne volania inline funkcii
#include "bitset.h"
#ifdef USE_INLINE

extern void bitset_free(bitset_t jmeno_pole);
extern bitset_index_t bitset_size(bitset_t jmeno_pole);
extern void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, int vyraz);
extern bitset_index_t bitset_getbit(bitset_t jmeno_pole, bitset_index_t index);

#endif
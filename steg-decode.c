// steg-decode.c
// Řešení IJC-DU1, příklad a), 22.3.2022
// Autor: Jakub Kontrík, FIT
// Přeloženo: gcc 11.2
// Dekodovanie spravy zo suboru
#include <stdio.h>
#include <stdlib.h>

#include "bitset.h"
#include "eratosthenes.h"
#include "ppm.h"
#include "error.h"

int main(int argc, char **argv){
    struct ppm *p;
    if(argc != 2) {
        error_exit("steg.decode: Wrong program arguments!");
    }
    int lsb_mask = 0x01;
    int char_buffer_mask = 0;
    int char_buffer = 0;
    p = ppm_read(argv[1]);
    //kedze chybny format vyhadzuje iba warning tak treba dodatocnu kontrolu aby sa nepracovalo s NULL ptr
    if (p == NULL) {
        error_exit("steg-decode: ppm_read returning null!");
    }
    bitset_alloc(bitarr,p->ysize * p->ysize * 3);
    Eratosthenes(bitarr);
    // pocitadlo pre naplnenie znaku potrebnym poctom bitov
    int cycle = 0;
    for (unsigned i = 29; p->data[i]!= EOF; i++) {
        if(!bitset_getbit(bitarr, i)) {
            // zistenie lsb ci je 0 alebo 1 a posun v char maske na potrebne miesto
            char_buffer_mask = (p->data[i] & lsb_mask) << cycle;
            // logicke scitanie masky a bufferu
            char_buffer = char_buffer | char_buffer_mask;
            cycle++;
        }
        // vypis charu na stdout a vynulovanie
        if(cycle == 8) {
            if(char_buffer == '\0') {
                break;
            }
            printf("%c", char_buffer);
            cycle = 0;
            char_buffer = 0;
        }

    }
    printf("\n");
    if(char_buffer != '\0') {
        bitset_free(bitarr);
        ppm_free(p);
        error_exit("steg_decode: Data are not ended correctly!");
    }
    bitset_free(bitarr);
    ppm_free(p);
    return 0;
}
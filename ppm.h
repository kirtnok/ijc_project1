// ppm.h
// Řešení IJC-DU1, příklad a), 22.3.2022
// Autor: Jakub Kontrík, FIT
// Přeloženo: gcc 11.2
/* Hlavicka pre nacitavanie dat z ppm pridane 2
funkcie pre kontrolu bielych znakov a prevod pola na cislo*/
#ifndef PPM_H
#define PPM_H
#include <stdbool.h>
struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];    // RGB bajty, celkem 3*xsize*ysize
};

bool is_white_space(int c);
unsigned int convert_arr(char *arr);
struct ppm *ppm_read(const char *filename);
void ppm_free(struct ppm *p);
#endif /*PPM_H*/
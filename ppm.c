// ppm.c
// Řešení IJC-DU1, příklad a), 22.3.2022
// Autor: Jakub Kontrík, FIT
// Přeloženo: gcc 11.2
/* Nacitavanie dat z obrazku do pola. 
Kontrola formatu "P6" "255" a nacitavanie velkosti xsize ysize.*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "ppm.h"
#include "error.h"
#include "bitset.h"
// kontrola ci dany znak je "biely"
bool is_white_space(int c){
    if (c == '\n' || c == ' ' || c == '\f' || c == '\v' || c == '\r' || c == '\t'){
        return true;
    }
    return false;
}
// prevod pola pri xsize a ysize na cislo
unsigned int convert_arr(char *arr){
    int k = 0;
    for (int i = 0; arr[i]!= '\0'; i++) {
        if(((int)arr[i]-48) > 9 || 0 > ((int)arr[i]-48)) {
            error_exit("ppm.c: Character in size format!");
        }
        k = 10 * k + ((int)arr[i])-48;
    }
    return k;

}
struct ppm * ppm_read(const char *filename){
    FILE *fp = fopen(filename,"rb");
    if (fp == NULL) {
        error_exit("ppm.c: Error oppening file!");
        fclose(fp);

    }
    //nacitavanie znakov
    int c = 0;
    //pole pre P6 format zakoncene "\0" aby sa dal skontrolovat cez strcmp
    char p6_format[3] ={'\0'};
    // polia na xsize a ysize povolene maximum do 8000 cize 4 cifry + "\0"
    char xsize[5] = {'\0'};
    char ysize[5] = {'\0'};
    // kontrola formatu 255
    char number_format[4] ={'\0'};
    // nactianie pomocou fscanf prvy string az po prvy prazdny znak
    int a = fscanf(fp, "%s",p6_format);
    // zahodenie returnu fscanf (nepouzivam ho)
    (void)a;
    // kontrola formatu
    if(strcmp(p6_format, "P6") != 0) {
        warning_msg("ppm: Wrong ppm format!");
        fclose(fp);
        return NULL;
    }
    // nacitanie 4 cifier z x a y size
    a = fscanf(fp, "%4s",xsize);
    c = fgetc(fp);
    // pokial nie je dalsi znak prazdny tak bolo cislo vacsie ako 8000
    if(!is_white_space(c)) {
        fclose(fp);
        error_exit("ppm: Xsize is greater than 8000!");
    }

    a = fscanf(fp, "%4s",ysize);
    c = fgetc(fp);
    if(!is_white_space(c)) {
        fclose(fp);
        error_exit("ppm: Ysize is greater than 8000!");
    }
    // kontrola "255" formatu
    a = fscanf(fp, "%s",number_format);
    if(strcmp(number_format, "255") != 0) {
        warning_msg("ppm: Wrong ppm format!");
        fclose(fp);
        return NULL;
    }
    c = fgetc(fp);
    // alokacia struktury pre data a velkosti
    struct ppm *allocation = malloc((sizeof(struct ppm) + convert_arr(xsize)*convert_arr(ysize)*3));

    if (allocation == NULL) {
        fclose(fp);
        error_exit("ppm: Unsuccessful allocation!");
    }
    allocation->xsize=convert_arr(xsize);
    allocation->ysize=convert_arr(ysize);
    if (allocation->xsize >8000 || allocation->ysize >8000) {
        fclose(fp);
        free(allocation);
        error_exit("ppm: Size x or y is greater than 8000!");
    }
    // nacitanie az po koniec suboru
    bitset_index_t count = 0;
    while ((c = fgetc(fp)) != EOF) {
        allocation->data[count] = c;
        count++;
    }
    fclose(fp);
    return allocation;
}

void ppm_free(struct ppm *p){
    free(p);
}
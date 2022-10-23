// error.c
// Řešení IJC-DU1, příklad a), 22.3.2022
// Autor: Jakub Kontrík, FIT
// Přeloženo: gcc 11.2
// Modul na spracuvavanie chyb a vypis errorov
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "error.h"

void warning_msg(const char *fmt, ...){
    // nacitavanie premenneho poctu argumentov
    va_list vlist;
    va_start(vlist, fmt);
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, vlist);
    fprintf(stderr, "\n");
    va_end(vlist);
}

void error_exit(const char *fmt, ...){
    va_list vlist;
    va_start(vlist, fmt);
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, vlist);
    fprintf(stderr, "\n");
    va_end(vlist);
    exit(1);
}
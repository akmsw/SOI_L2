/**
 * @file mainL2.c
 * @author Bonino, Francisco Ignacio (franbonino82@gmail.com).
 * @brief Laboratorio #2 de Sistemas Operativos I - FCEFyN - UNC
 * @version 1.0
 * @since 2021-08-15
 * @bug No known bugs.
 */

// Librerías a utilizar.

#include "include/file_utilities.h"
#include "include/lab2_utilities.h"

// Programa principal.

int main(void)
{
    fprintf(stdout, ">   EJ. 1 - C-STRINGS\n\n");

    meminfo_display();
    cpuinfo_display();

    fprintf(stdout, "\n\n>   EJ. 2 - ARRAYS\n\n");

    display_uppercase("/proc/version");

    return 0;
}
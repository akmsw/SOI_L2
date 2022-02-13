/**
 * @file file_utilities.h
 * @author Bonino, Francisco Ignacio (franbonino82@gmail.com).
 * @brief Header de librería con funciones útiles generales para archivos.
 * @version 1.0
 * @since 2021-08-18
 */

#ifndef __FILE_UTILITIES__
#define __FILE_UTILITIES__

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_MAX_LEN 4096 // Máxima cantidad de caracteres por string. Valor sugerido por POSIX.

void display_uppercase(char *);

int get_value(char *, char *, char *);

char *search_line(FILE *, char *, char *);

bool open_file_r(FILE **, char *);

#endif
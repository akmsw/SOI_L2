/**
 * @file lab2_utilities.h
 * @author Bonino, Francisco Ignacio (franbonino82@gmail.com).
 * @brief Librería con funciones útiles particulares para el laboratorio #2.
 * @version 1.0
 * @since 2021-08-18
 */

#include "lab2_utilities.h"
#include "file_utilities.h"

/**
 * @brief Esta función se encarga de mostrar en pantalla
 *        información relacionada a la memoria del sistema.
 * 
 * @details Se muestra en pantalla el total de memoria RAM del
 *          sistema, la cantidad de RAM utilizada, la cantidad
 *          de RAM disponible y la cantidad de memoria swap
 *          ocupada. Todo se extrae del archivo /proc/meminfo.
 */
void meminfo_display(void)
{
    char meminfo_buffer[STR_MAX_LEN];
    char aux_buffer[STR_MAX_LEN];

    snprintf(meminfo_buffer, sizeof(meminfo_buffer), "------RAM memory info------\n");

    float total_ram = (float)get_value("MemTotal", "/proc/meminfo", ":") / 1000;
    float free_ram = (float)get_value("MemFree", "/proc/meminfo", ":") / 1000;
    float available_ram = (float)get_value("MemAvailable", "/proc/meminfo", ":") / 1000;
    float total_swap = (float)get_value("SwapTotal", "/proc/meminfo", ":") / 1000;
    float free_swap = (float)get_value("SwapFree", "/proc/meminfo", ":") / 1000;

    sprintf(aux_buffer, "Total RAM       : %8.2f [MB]\n", total_ram);
    strcat(meminfo_buffer, aux_buffer);

    sprintf(aux_buffer, "Free RAM        : %8.2f [MB]\n", free_ram);
    strcat(meminfo_buffer, aux_buffer);

    sprintf(aux_buffer, "Available RAM   : %8.2f [MB]\n", available_ram);
    strcat(meminfo_buffer, aux_buffer);

    sprintf(aux_buffer, "Occupied swap   : %8.2f [MB]\n", (total_swap - free_swap));
    strcat(meminfo_buffer, aux_buffer);

    fprintf(stdout, "%s", meminfo_buffer);
}

/**
 * @brief Esta función se encarga de mostrar en pantalla
 *        información relacionada a la unidad central de
 *        procesamiento (CPU) del sistema.
 * 
 * @details Se muestra en pantalla el modelo de CPU del
 *          sistema, la cantidad de cores y la cantidad
 *          de threads por core. Toda la información se
 *          extrae del archivo /proc/cpuinfo mediante las
 *          funciones search_line y get_value.
 */
void cpuinfo_display(void)
{
    FILE *cpufile = NULL;

    char cpuinfo_buffer[STR_MAX_LEN];
    char aux_buffer[STR_MAX_LEN];

    int threads = get_value("siblings", "/proc/cpuinfo", ":");
    int cores = get_value("cpu cores", "/proc/cpuinfo", ":");

    snprintf(cpuinfo_buffer, sizeof(cpuinfo_buffer), "\n---------CPU info----------\n");

    strtok(search_line(cpufile, "model name", "/proc/cpuinfo"), ":");

    sprintf(aux_buffer, "CPU model       : %s", strtok(NULL, ":"));
    strcat(cpuinfo_buffer, aux_buffer);

    sprintf(aux_buffer, "CPU cores       : %2d\n", cores);
    strcat(cpuinfo_buffer, aux_buffer);

    sprintf(aux_buffer, "Threads/Cores   : %2d", threads / cores);
    strcat(cpuinfo_buffer, aux_buffer);

    fprintf(stdout, "%s", cpuinfo_buffer);
}
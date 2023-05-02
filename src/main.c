/**
 * @file    main.c
 * @author  eziojognap
 * @date    16/4/23
 * @brief   Archivo main.c del trabajo practico 2 de Sistemas Embebidos UNT
 **/

/************************************* INCLUDES ***************************************************/
#include "alumno.h"
#include <stdio.h>

/************************************* EXTERN VARIABLES *******************************************/

/************************************* PRIVATE MACROS AND DEFINES *********************************/

/************************************* PRIVATE TYPEDEFS *******************************************/

/************************************* STATIC VARIABLES *******************************************/

/************************************* GLOBAL VARIABLES *******************************************/

/************************************* STATIC FUNCTION PROTOTYPES *********************************/

/************************************* STATIC FUNCTIONS *******************************************/

/************************************* GLOBAL FUNCTIONS *******************************************/

/// @brief Funcion Principal del archivo main.c

int main(void) {

    const puntero_alumno_s yo = CrearAlumno("Jogna Prat", "Ezio", 41649861);

    char cadena_datos_alumno[128];

    if (Serializar(yo, cadena_datos_alumno, sizeof(cadena_datos_alumno)) >= 0) {
        printf("%s\n", cadena_datos_alumno);
    } else {
        printf("Error al serializar\n");
    }
    return 0;
}
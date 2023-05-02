/***************************************************************************************************
 * @file    alumno.h
 * @author  eziojognap
 * @date    16/4/23
 * @brief   Archivo main.c del trabajo practico 2 de Sistemas Embebidos UNT
 **************************************************************************************************/
/************************************* C++ compilar como C ****************************************/
#ifdef __cplusplus /*Esta definición se usa para compilar en c codigo que es de c++*/
extern "C" {
#endif

/************************************* INCLUDES ***************************************************/
#include <stdint.h>

/************************************* MACROS AND DEFINES *****************************************/
#ifndef ALUMNO_H
#define ALUMNO_H
#endif

#define FIELD_SIZE 50 //!< Define un Macro que tiene como valor 50, se usa como una ctte

/************************************* TYPEDEFS ***************************************************/

typedef struct alumno_s *puntero_alumno_s; //!< puntero_alumno_s es un puntero al tipo de datos estructura alumno_s que esta definida en alumno.c

/************************************* EXPORTED VARIABLES *****************************************/

/************************************* GLOBAL FUNCTION PROTOTYPES *********************************/

/// @brief Devuelve un puntero alumno_t al tipo de datos estructura alumno_s
/// @param apellido
/// @param nombre
/// @param documento
/// @return
puntero_alumno_s CrearAlumno(char *apellido, char *nombre, int documento);

// Comento las siguientes dos funciones porque no las usamos
/// Función para obtener el nombre completo
// int GetCompleto(alumno_t alumno, char cadena[], uint32_t espacio);

/// Función para obtener el documento
// int GetDocumento(alumno_t alumno);

/// @brief Funcion serializar:
/// @param alumno Puntero a la estructura con los datos del alumno
/// @param cadena Puntero a la cadena resultado
/// @param espacio Espacio disponible en la cadena de resultado
/// @return
int Serializar(puntero_alumno_s alumno, char cadena[], uint32_t espacio);

#ifdef __cplusplus /*Con esto se cierra la la def condicional para compilar en c codigo que es de  \
                      c++*/
}
#endif

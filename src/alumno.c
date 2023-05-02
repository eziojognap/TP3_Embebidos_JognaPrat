/***************************************************************************************************
 * @file    alumno.c
 * @author  eziojognap
 * @date    16/4/23
 * @brief   Archivo alumno.c donde se serializan los datos.
 **************************************************************************************************/

/************************************* INCLUDES ***************************************************/
#include "alumno.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************* EXTERN VARIABLES *******************************************/

/************************************* PRIVATE MACROS AND DEFINES *********************************/

/************************************* PRIVATE TYPEDEFS *******************************************/

/// @brief Estructura que almacena los datos del alumno
struct alumno_s {
    char apellido[FIELD_SIZE]; //!< Almacena el apellido del alumno
    char nombre[FIELD_SIZE];   //!< Almacena el nombre del alumno
    uint32_t documento;        //!< Almacena el numero de documento del alumno
    bool ocupado; //!< se pone ocupado porque los casilleros se inicializan en 0, entonces al estar
                  //!< en cero ocupado seria falso
};

/************************************* STATIC VARIABLES *******************************************/

/************************************* GLOBAL VARIABLES *******************************************/

/************************************* STATIC FUNCTION PROTOTYPES *********************************/

/************************************* STATIC FUNCTIONS *******************************************/
// Son funciones locales
static int SerializarCadena();
static int SerializarNumero();

static int SerializarCadena(const char *campo, const char *valor, char *cadena, int espacio) {
    return snprintf(cadena, espacio, "\"%s\":\"%s\",", campo, valor);
}

static int SerializarNumero(const char *campo, int valor, char *cadena, int espacio) {
    return snprintf(cadena, espacio, "\"%s\":\"%d\",", campo, valor);
}

/************************************* GLOBAL FUNCTIONS *******************************************/

/// @brief Funcion crear alumno:
///         devuelve un puntero a la estructura que almacena los datos de los alumnos
/// @param apellido char indica que es una cadena de caracteres y el * indica que es un puntero a
/// eso
/// @param nombre igual al anterior
/// @param documento
/// @return
puntero_alumno_s CrearAlumno(char *apellido, char *nombre, int documento) {
    static struct alumno_s instancias[50] = {0}; //!< Con esto me aseguro que solo esta funcion
                                                 //!< puede crear el espacio para los alumnos
    /// No me puedo olvidar del static porque si no se destruye el espacio que estoy creando cuando
    /// salgo de la funcion
    /// Con el static el espacio se crea antes de empezar la ejecucion del programa

    puntero_alumno_s valor_puntero;

    for (int i = 0; i < 50; i++) {
        if (instancias[i].ocupado == 0) {
            strcpy(instancias[i].apellido, apellido); // cuando se usa puntero va la flecha, cuando
                                                      // se usa la estructura va el punto (.)
            strcpy(instancias[i].nombre, nombre);
            instancias[i].documento = documento;
            valor_puntero = &instancias[i];
        } else {
            printf("No hay espacio en memoria\n");
            valor_puntero = NULL;
        }
    }
    return valor_puntero;
}
// *algo indica que algo es una direccion de memoria y apunta al casillero donde apunta algo, no a
// algo &dato devuelve la direccion de memoria (un puntero) a dato Comento las funciones porque no
// las usamos

/// @brief Funcion serializar
/// @param alumno puntero a la estructura alumno
/// @param cadena cadena de caracteres
/// @param espacio
/// @return
int Serializar(puntero_alumno_s alumno, char cadena[], uint32_t espacio) {
    int disponibles = espacio;
    int resultado;

    cadena[0] = '{';
    cadena++;
    disponibles--;
    resultado = SerializarCadena("apellido", alumno->apellido, cadena, disponibles);

    if (resultado > 0) {
        disponibles = disponibles - resultado;
        cadena = cadena + resultado;
        resultado = SerializarCadena("nombre", alumno->nombre, cadena, disponibles);
    }

    if (resultado > 0) {
        disponibles = disponibles - resultado;
        cadena = cadena + resultado;
        resultado = SerializarNumero("documento", alumno->documento, cadena, disponibles);
    }

    if (resultado > 0) {
        cadena = cadena + resultado;
        *(cadena - 1) = '}';
        resultado = espacio - disponibles;
    }

    return resultado;
}

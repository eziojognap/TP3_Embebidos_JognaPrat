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

/************************************* GLOBAL FUNCTIONS *******************************************/
static int SerializarCadena();
static int SerializarNumero();

static int SerializarCadena(const char *campo, const char *valor, char *cadena, int espacio) {
    return snprintf(cadena, espacio, "\"%s\":\"%s\",", campo, valor);
}

static int SerializarNumero(const char *campo, int valor, char *cadena, int espacio) {
    return snprintf(cadena, espacio, "\"%s\":\"%d\",", campo, valor);
}

/// @brief Funcion crear alumno:
///    usamos un puntero "resultado" tipo alumno_t a la estructura. Para eso antes necesitamos
///    generar espacios de memoria donde guardar los datos, ya que, tenemos un puntero a la
///    estructura, no la estructura.
/// @param apellido
/// @param nombre
/// @param documento
/// @return
alumno_t CrearAlumno(char *apellido, char *nombre, int documento) {
    static struct alumno_s instancias[50] = {0}; //!< Con esto me aseguro que solo esta funcion
                                                 //!< puede crear el espacio para los alumnos
    /// No me puedo olvidar del static porque si no se destruye el espacio que estoy creando cuando
    /// salgo de la funcion
    /// Con el static el espacio se crea antes de empezar la ejecucion del programa
    alumno_t resultado = malloc(sizeof(struct alumno_s)); //!< memory alloc me brinda un
                                                          //!< espacio de memoria libre
    strcpy(resultado->apellido, apellido);                //!< strcpy es para copiar una string
    strcpy(resultado->nombre, nombre);
    resultado->documento = documento;
    return resultado;
}

// Comento las funciones porque no las usamos
/// Función para obtener el nombre completo
// int GetCompleto(alumno_t alumno, char cadena[], uint32_t espacio) {
//     return NULL;
// }

/// Función para obtener el documento
// int GetDocumento(alumno_t alumno) {
//     return NULL;
// }

/// @brief Funcion serializar
/// @param alumno
/// @param cadena
/// @param espacio
/// @return
int Serializar(alumno_t alumno, char cadena[], uint32_t espacio) {
    int disponibles = espacio;
    int resultado;

    cadena[0] = '{';
    cadena++;
    disponibles--;
    resultado = SerializarCadena("apellido", alumno->apellido, cadena, disponibles);

    if (resultado > 0) {
        disponibles -= resultado;
        cadena += resultado;
        resultado = SerializarCadena("nombre", alumno->nombre, cadena, disponibles);
    }

    if (resultado > 0) {
        disponibles -= resultado;
        cadena += resultado;
        resultado = SerializarNumero("documento", alumno->documento, cadena, disponibles);
    }

    if (resultado > 0) {
        cadena += resultado;
        *(cadena - 1) = '}';
        resultado = espacio - disponibles;
    }

    return resultado;
}

/* Buffer.h    Definiciones del módulo Buffer */
#if !defined(BUFFER_H)

#define  BUFFER_H

#include "Varios.h"

#define SIZE_BUFFER 300

typedef float Bf_data;
typedef int Bf_pointer;


typedef struct Buffer_Control Buffer_Control;
struct Buffer_Control
{
    /* Banderas */
    volatile unsigned char full[NUM_CHANNELS];  // 1 si está lleno, 0 si no
    volatile unsigned char active; // 1 si el buffer está activo, 0 si no

    /* Datos */
    volatile Bf_data datos[NUM_CHANNELS][SIZE_BUFFER];

    /* Control del tamaño del buffer */
    volatile Bf_pointer write[NUM_CHANNELS];  // Posición de escritura
    Bf_pointer read[NUM_CHANNELS];    // Posición de lectura
    Bf_pointer cont[NUM_CHANNELS];    // Valores guardados en un instante
    Bf_pointer total;   // Total de valores a guardar
};


///////////////////////////////////////////
/* ======= Rutinas ======== */

/* Rutina para iniciar el módulo (su estructura de datos) */   
void Bf_Inicie(Buffer_Control *buf, Bf_pointer total);

/* Rutina para verificar si el buffer está o no lleno */
char Bf_Lleno(Buffer_Control *buf, int channel);

/* Rutina para verificar si el buffer está vacío */
char Bf_Vacio(Buffer_Control *buf, int channel);

/* Rutina para subir un dato al buffer */
char Bf_Subir_Dato(Buffer_Control *buf, int channel, Bf_data write);

/* Rutina para bajar un dato del buffer */
char Bf_Bajar_Dato(Buffer_Control *buf, int channel, Bf_data *read);

/* Rutina para verificar cuantos espacios tiene libres */
char Bf_Libre(Buffer_Control *buf, int channel, Bf_pointer *free);

#endif

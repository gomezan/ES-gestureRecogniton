/* Caracterizador.h    Definiciones del m�dulo de extracción de caracteristicas */
#if !defined(CARACTERIZADOR_H)

#define  CARACTERIZADOR_H

#include "Segmentador.h"

//Definición de número de caracteristicas
#define NUM_CAR 11

/* Tipo de dato para vector de caracteristicas */
typedef float Cr_Caracteristicas;

//Estructura de control del modulo caracterizador
typedef struct Cr_Control Cr_Control;
struct Cr_Control
{  

  /* Ventana de segmentación */
    volatile Sg_canalData *wnd;

    /* Vector de caracteristicas */
    volatile Cr_Caracteristicas *vec;

  /* Arreglo de funciones a usar para extraer caracteristicas */
  Cr_Caracteristicas (*funciones[NUM_CAR])(const Cr_Caracteristicas*, int);              
   
};
   
/* ======= Rutinas ======== */
/* Rutina para iniciar el módulo (su estructura de datos) */   
char Cr_Inicie (Cr_Control *cr, Sg_canalData *wnd, Cr_Caracteristicas *vec);
                  
/* Rutina para procesar el módulo (dentro del loop de polling) */				
void Cr_Procese (Cr_Control *cr);

/* ===== RUTINAS DE INTERFAZ ====== */
Cr_Caracteristicas suma(const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas promedio(const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas rms(const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas varianza(const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas desviacion_estandar(const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas MAV(const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas WL(const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas ZC(const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas SSC(const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas skewness(const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas kurtosis(const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas integrar(const Cr_Caracteristicas* arr, int size);

/* == FIN DE RUTINAS DE INTERFAZ == */

#endif
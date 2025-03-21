/* Caracterizador.h    Definiciones del m�dulo de extracción de caracteristicas */
#if !defined(CARACTERIZADOR_H)

#define  CARACTERIZADOR_H

#include "Segmentador.h"
#include <arduinoFFT.h>

//Definición de número de caracteristicas
#define NUM_CAR_T 12
#define NUM_CAR_F 4

#define WAMP_THRESHOLD 140.0 // Umbral para la detección de cambios en WAMP
#define SAMPLES  128 //Window for precessing FFT
#define FS 500 


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
  Cr_Caracteristicas (*funciones[(NUM_CAR_T + NUM_CAR_F)])(Cr_Control *cr,const Cr_Caracteristicas*, int);   

  /*Vectores de funcionamiento de la FFT*/
  volatile Cr_Caracteristicas *vReal;  
  volatile Cr_Caracteristicas *vImag;

  /* Create FFT object */
  ArduinoFFT<Cr_Caracteristicas> FFT;  
           
};
   
/* ======= Rutinas ======== */
/* Rutina para iniciar el módulo (su estructura de datos) */   
char Cr_Inicie (Cr_Control *cr, Sg_canalData *wnd, Cr_Caracteristicas *vec,
                Cr_Caracteristicas *vReal,
                Cr_Caracteristicas *vImag,
                ArduinoFFT<Cr_Caracteristicas> FFT);
                  
/* Rutina para procesar el módulo (dentro del loop de polling) */				
void Cr_Procese (Cr_Control *cr);

/* ===== RUTINAS DE INTERFAZ ====== */
void printVreal(Cr_Control *cr);
void calcular_FFT(Cr_Control *cr);
Cr_Caracteristicas suma(Cr_Control *cr,const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas Promedio(Cr_Control *cr,const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas RMS(Cr_Control *cr,const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas Varianza(Cr_Control *cr,const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas STD(Cr_Control *cr,const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas MAV(Cr_Control *cr,const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas WL(Cr_Control *cr,const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas ZC(Cr_Control *cr,const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas SSC(Cr_Control *cr,const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas skewness(Cr_Control *cr,const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas kurtosis(Cr_Control *cr,const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas iEMG(Cr_Control *cr,const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas WAMP(Cr_Control *cr,const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas MAS(Cr_Control *cr,const Cr_Caracteristicas* arr, int size);

/* == FIN DE RUTINAS DE INTERFAZ == */

#endif
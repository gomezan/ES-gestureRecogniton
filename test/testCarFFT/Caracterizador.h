/* Caracterizador_mod.h    Definiciones del módulo de extracción de caracteristicas */

#if !defined(CARACTERIZADOR_H)
#define  CARACTERIZADOR_H

#include "Segmentador.h"
#include "Varios.h"

#define NUM_CAR_T 9
#define NUM_CAR_F 6
#define WAMP_THRESHOLD 140.0
#define SAMPLES  128

typedef float Cr_Caracteristicas;

typedef struct Cr_FuncionCaracteristica Cr_FuncionCaracteristica;

//Estructura para almacenar catactericas de tiempo
struct Cr_FuncionCaracteristica_time {
    Cr_Caracteristicas (*func)(const Cr_Caracteristicas*, int);
    Cr_Caracteristicas min;
    Cr_Caracteristicas max;
};

//Estructura para almacenar catactericas de frecuencia
struct Cr_FuncionCaracteristica_freq {
    Cr_Caracteristicas (*func)(const Cr_Caracteristicas *);
    Cr_Caracteristicas min;
    Cr_Caracteristicas max;
};

typedef struct Cr_Control Cr_Control;
struct Cr_Control {

    /*Ventana segmentada*/
    volatile Sg_canalData *wnd;
    /*Vector de caracteristicas*/
    volatile Cr_Caracteristicas *vec;

    /*Caracteristicas*/
    Cr_FuncionCaracteristica_time funcionesTime[NUM_CHANNELS][NUM_CAR_T];
    Cr_FuncionCaracteristica_freq funcionesFreq[NUM_CHANNELS][NUM_CAR_F];
};

char Cr_Inicie (Cr_Control *cr, Sg_canalData *wnd, Cr_Caracteristicas *vec);

void Cr_Procese (Cr_Control *cr);

//Agregar caracteristica
Cr_FuncionCaracteristica_time Cr_CrearFuncion_time(Cr_Caracteristicas (*f)(const Cr_Caracteristicas*, int), Cr_Caracteristicas min, Cr_Caracteristicas max);
Cr_FuncionCaracteristica_freq Cr_CrearFuncion_freq(Cr_Caracteristicas (*f)(const Cr_Caracteristicas*), Cr_Caracteristicas min, Cr_Caracteristicas max);


//Caracteristicas
Cr_Caracteristicas suma(const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas Promedio(const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas RMS(const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas Varianza(const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas STD(const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas MAV(const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas WL(const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas ZC(const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas SSC(const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas skewness(const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas kurtosis(const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas iEMG(const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas WAMP(const Cr_Caracteristicas* arr, int size);
Cr_Caracteristicas PF(const Cr_Caracteristicas* arr);
Cr_Caracteristicas PM(const Cr_Caracteristicas* arr);
Cr_Caracteristicas MNM(const Cr_Caracteristicas* arr);
Cr_Caracteristicas MNF(const Cr_Caracteristicas* arr);
Cr_Caracteristicas MDM(const Cr_Caracteristicas* arr);
Cr_Caracteristicas MDF(const Cr_Caracteristicas* arr);

#endif
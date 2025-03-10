/* Caracterizador_mod.h    Definiciones del módulo de extracción de caracteristicas */

#if !defined(CARACTERIZADOR_H)
#define  CARACTERIZADOR_H

#include "Segmentador.h"

#define NUM_CAR 12
#define WAMP_THRESHOLD 140.0
#define SAMPLES  128
#define FS 500
#define NUM_CHANNELS 8  // Define number of channels

typedef float Cr_Caracteristicas;

typedef struct Cr_FuncionCaracteristica Cr_FuncionCaracteristica;

struct Cr_FuncionCaracteristica {
    Cr_Caracteristicas (*func)(const Cr_Caracteristicas*, int);
    Cr_Caracteristicas min;
    Cr_Caracteristicas max;
};

typedef struct Cr_Control Cr_Control;
struct Cr_Control {
    volatile Sg_canalData *wnd;
    volatile Cr_Caracteristicas *vec;
    Cr_FuncionCaracteristica funciones[NUM_CHANNELS][NUM_CAR];
};

char Cr_Inicie (Cr_Control *cr, Sg_canalData *wnd, Cr_Caracteristicas *vec);
void Cr_Procese (Cr_Control *cr);
Cr_FuncionCaracteristica Cr_CrearFuncion(Cr_Caracteristicas (*f)(const Cr_Caracteristicas*, int), Cr_Caracteristicas min, Cr_Caracteristicas max);

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
Cr_Caracteristicas WAMP(const Cr_Caracteristicas* arr, int size);

#endif
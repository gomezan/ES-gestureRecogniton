/* display.h    Definiciones del m�dulo Display */
#if !defined(DISPLAY_H)

#define  DISPLAY_H

#include <Tiempo.h>
#include <model.h>

#define NUM_MUERTO 0x10  /// Apagado
#define PERIODO_BASE 10 // REVIAR

//Estructura de control del display
typedef struct Dp_Control Dp_Control;

struct Dp_Control
{                  
   
   /* Almacena el número a imprimir */
   IA_gesture prediction;
   
   /* Interfaz al módulo de tiempo */
   Tm_Num   n_periodo;
   
   };
   
/* ======= Rutinas ======== */
/* Rutina para iniciar el módulo (su estructura de datos) */   
char Dp_Inicie (Dp_Control *dp, Tm_Num n_periodo);
                  
/* Rutina para procesar el módulo (dentro del loop de polling) */				
void Dp_Procese (Dp_Control *dp);

/* ===== RUTINAS DE INTERFAZ ====== */
void Dp_updatePrediction(Dp_Control *dp, IA_gesture pred);

/* == FIN DE RUTINAS DE INTERFAZ == */

#endif
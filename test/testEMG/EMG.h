/* EMG.h    Definiciones del m�dulo de adqusición de señales */
#if !defined(EMG_H)

#define  EMG_H

#include <Tiempo.h>

#define PERIODO_BASE 1 // Programado a 500 Hz

//Estructura de control del display
typedef struct EMG_Control EMG_Control;

struct EMG_Control
{                  
   
   /* Interfaz al módulo de tiempo */
   Tm_Num   n_periodo;
   
   };
   
/* ======= Rutinas ======== */
/* Rutina para iniciar el módulo (su estructura de datos) */   
char EMG_Inicie (EMG_Control *emg, Tm_Num n_periodo);
                  
/* Rutina para procesar el módulo (dentro del loop de polling) */				
void EMG_Procese (EMG_Control *emg);

/* ===== RUTINAS DE INTERFAZ ====== */
//pendiente

/* == FIN DE RUTINAS DE INTERFAZ == */

#endif
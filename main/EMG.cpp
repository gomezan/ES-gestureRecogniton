/* EMG.c    implementaci�n del módulo de adqusición de señales */

#include <Tiempo.h>
#include "EMG.h"
#include "Varios.h"

//
extern Tm_Control c_tiempo;


/* Rutina para iniciar el módulo (su estructura de datos) */   
char EMG_Inicie (EMG_Control *emg, 
                Tm_Num n_periodo)
   {
   
   emg->n_periodo = n_periodo;
   if ( !Tm_Inicie_periodo(&c_tiempo, n_periodo, PERIODO_BASE) )
      return NO;

   return SI;
   };


                  
/* Rutina para procesar el módulo (dentro del loop de polling) */				
void EMG_Procese (EMG_Control *emg){

    Serial.println("Coming soon");
   
   };

/* ===== RUTINAS DE INTERFAZ ====== */
/* Rutina para activar un canal. Indica si se pudo activar. */


/* == FIN DE RUTINAS DE INTERFAZ == */

/* display.c    implementaci�n del módulo Display */

#include "display.h"
#include <Tiempo.h>
#include "Varios.h"

//
extern Tm_Control c_tiempo;


/* Rutina para iniciar el módulo (su estructura de datos) */   
char Dp_Inicie (Dp_Control *dp, 
                Tm_Num n_periodo)
   {

   dp->prediction =NUM_MUERTO;
   
   dp->n_periodo = n_periodo;
   if ( !Tm_Inicie_periodo(&c_tiempo, n_periodo, PERIODO_BASE) )
      return NO;

   return SI;
   };


                  
/* Rutina para procesar el módulo (dentro del loop de polling) */				
void Dp_Procese (Dp_Control *dp){

    Serial.println(dp->prediction);
   
   };

/* ===== RUTINAS DE INTERFAZ ====== */
/* Rutina para activar un canal. Indica si se pudo activar. */
void Dp_updatePrediction(Dp_Control *dp, IA_gesture pred){
    
    dp->prediction =pred;

}

/* == FIN DE RUTINAS DE INTERFAZ == */

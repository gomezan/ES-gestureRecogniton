/* Segmentador.c    implementaci�n del módulo que contiene la logica de la segmentación de las señales en ventanas */

#include <Tiempo.h>
#include <Buffer.h>
#include "Varios.h"
#include "Segmentador.h"

extern Tm_Control c_tiempo;
extern Buffer_Control c_buff;


/* Rutina para iniciar el módulo (su estructura de datos) */   
char Sg_Inicie (Sg_Control *sg, 
                Tm_Num n_periodo, 
                Sg_canalData *wnd)
   {

   //inicializar ventana
    sg->wnd=wnd;
   
   //Inicializar periodo
   sg->n_periodo = n_periodo;
   if ( !Tm_Inicie_periodo(&c_tiempo, n_periodo, PERIODO_SG) )
      return NO;

   return SI;
   };


                  
/* Rutina para procesar el módulo (dentro del loop de polling) */				
void Sg_Procese (Sg_Control *sg){

  Bf_pointer *ptr;
  int fill=SIZE_BUFFER-Bf_Libre(&c_buff, 0, ptr);

  if(fill>=WINDOW_SIZE){

    for (int j=0; j< WINDOW_SIZE; j++){

      float inputSignals[NUM_CHANNELS];

      for (int i = 0; i < NUM_CHANNELS; i++)  
      Bf_Bajar_Dato(&c_buff,i,&inputSignals[i]);
      
      // Imprimir los valores de las salidas de los 8 canales
        for (int i = 0; i < NUM_CHANNELS; i++) {
            Serial.print(inputSignals[i]);
            if(i!=NUM_CHANNELS-1){
              Serial.print(","); 
            } else{
                Serial.println();
            }
            
        }

  }

  }
  
   
};


/* ===== RUTINAS DE INTERFAZ ====== */



/* == FIN DE RUTINAS DE INTERFAZ == */

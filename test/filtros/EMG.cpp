/* EMG.c    implementaci�n del módulo de adqusición de señales */

#include <Tiempo.h>
#include "EMG.h"
#include "Varios.h"
#include <Buffer.h>

//
extern Tm_Control c_tiempo;
extern Buffer_Control c_buff;

/* Rutina para iniciar el módulo (su estructura de datos) */   
char EMG_Inicie (EMG_Control *emg, 
                Tm_Num n_periodo
                )  
   {
   //Inicializar periodo
   emg->n_periodo = n_periodo;
   if ( !Tm_Inicie_periodo(&c_tiempo, n_periodo, PERIODO_EMG) )
      return NO;

   return SI;
   };


                  
/* Rutina para procesar el módulo (dentro del loop de polling) */				
void EMG_Procese (EMG_Control *emg){

   EMG_data inputSignals[NUM_CHANNELS];

   // Leer valores de los pines analógicos
   for (int i = 0; i < NUM_CHANNELS; i++) {
       inputSignals[i] = analogRead(analogPins[i]);
   }
   
    //Almacenar datos en el buffer
    for (int i = 0; i < NUM_CHANNELS; i++) 
      Bf_Subir_Dato(&c_buff,i,inputSignals[i]);

   // Imprimir los valores de las salidas de los 8 canales
   /*
    for (int i = 0; i < NUM_CHANNELS; i++) {
        Serial.print(outputSignals[i], 4);
        if(i!=NUM_CHANNELS-1){
           Serial.print(","); 
        } else{
            Serial.println();
        }
        
    }

    */
    
   
};


/* ===== RUTINAS DE INTERFAZ ====== */



/* == FIN DE RUTINAS DE INTERFAZ == */

/* EMG.c    implementaci�n del módulo de adqusición de señales */

#include <Tiempo.h>
#include "EMG.h"
#include "Varios.h"
#include <Buffer.h>


extern Buffer_Control c_buff;

                  
/* Rutina para procesar el módulo (dentro del loop de polling) */				
void EMG_Procese (){

   EMG_data inputSignals[NUM_CHANNELS];

   // Leer valores de los pines analógicos
   for (int i = 0; i < NUM_CHANNELS; i++) {
       inputSignals[i] = static_cast<EMG_data>(analogRead(analogPins[i]));
   }
   
    //Almacenar datos en el buffer
    for (int i = 0; i < NUM_CHANNELS; i++)
      Bf_Subir_Dato(&c_buff,i,static_cast<Bf_data>(inputSignals[i]));

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

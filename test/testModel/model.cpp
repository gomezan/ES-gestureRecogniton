/* model.c    implementaci�n del módulo Display */

#include "BioAmp0.h"
#include <Arduino.h>
#include <tflm_esp32.h>
#include <eloquent_tinyml.h>

#include "model.h"
#include <Tiempo.h>
#include <display.h>
#include "Varios.h"

//modulos principales 
extern Tm_Control c_tiempo;
extern Dp_Control c_display;

// Definición de modelos Eloquent
Eloquent::TF::Sequential<TF_NUM_OPS, ARENA_SIZE> tf;

/* Rutina para iniciar el módulo (su estructura de datos) */   
char IA_Inicie (IA_Control *ia, algoritmo   modelo)
   {

    ia->modelo = modelo;

    tf.setNumInputs(84);
    tf.setNumOutputs(6);
 
    if (!tf.begin(BioAmp0).isOk()){
      Serial.println(tf.exception.toString());
      return NO;
    } 
        
   return SI;
   };


                  
/* Rutina para procesar el módulo (dentro del loop de polling) */				
void IA_Procese (IA_Control *ia){

    int a=0;
   
   };

/* ===== RUTINAS DE INTERFAZ ====== */
/* Rutina para activar un canal. Indica si se pudo activar. */
 char IA_Predict(IA_Control *ia, float x[84]){

  if (!tf.predict(x).isOk()) {
        Serial.println(tf.exception.toString());
        return NO;
    }

    Dp_updatePrediction(&c_display,tf.classification);
    return SI;  

 }
/* == FIN DE RUTINAS DE INTERFAZ == */

/* Segmentador.c    implementaci�n del módulo que contiene la logica de la segmentación de las señales en ventanas */

#include <Tiempo.h>
#include <Buffer.h>
#include <Segmentador.h>
#include <Filtrador.h>
#include "Varios.h"


extern Tm_Control c_tiempo;
extern Buffer_Control c_buff;
extern Fc_Control c_filter;

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

  Bf_pointer ltr;
  Bf_Libre(&c_buff, 0, &ltr);
  int fill=SIZE_BUFFER-ltr;


  if(fill>=WINDOW_SIZE){

    for (int j=0; j< WINDOW_SIZE; j++){
      for (int i = 0; i <  NUM_CHANNELS; i++){
        Sg_data input;
        Bf_Bajar_Dato(&c_buff,i, (Bf_data*)&input);
        sg->wnd[i].canal[j]=Fc_Procese (&c_filter, input, i);
      }  
    }

    // Imprimir los valores de las ventanas de los 8 canales -- vetana por ventana
    /*
        for (int i=0;i<NUM_CHANNELS;i++){
          for(int j=0;j<WINDOW_SIZE;j++){
            Serial.print(sg->wnd[i].canal[j]);
            Serial.print(",");
          }
          Serial.println();
        }
    */

    // Imprimir los valores de las ventanas de los 8 canales -- canal por canal
      for(int j=0;j<WINDOW_SIZE;j++){
      Serial.print(sg->wnd[0].canal[j]);
      Serial.print(",");
      Serial.print(sg->wnd[1].canal[j]);
      Serial.print(",");
      Serial.print(sg->wnd[2].canal[j]);
      Serial.print(",");
      Serial.print(sg->wnd[3].canal[j]);
      Serial.print(",");
      Serial.print(sg->wnd[4].canal[j]);
      Serial.print(",");
      Serial.print(sg->wnd[5].canal[j]);
      Serial.print(",");
      Serial.print(sg->wnd[6].canal[j]);
      Serial.print(",");
      Serial.print(sg->wnd[7].canal[j]);
      Serial.println();

      }
    
  }
};



/* ===== RUTINAS DE INTERFAZ ====== */



/* == FIN DE RUTINAS DE INTERFAZ == */

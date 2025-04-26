/* Segmentador.c    implementaci�n del módulo que contiene la logica de la segmentación de las señales en ventanas */

#include <Tiempo.h>
#include <Buffer.h>
#include <Caracterizador.h>
#include "Varios.h"
#include <Segmentador.h>
#include "Filtrador.h"


extern Tm_Control c_tiempo;
extern Buffer_Control c_buff;
extern Cr_Control c_car;
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

    //Estado inicial de la ventana
    sg->empty=SI;

   return SI;
   };


                  
/* Rutina para procesar el módulo (dentro del loop de polling) */						
void Sg_Procese(Sg_Control *sg) {
    Bf_pointer ltr;
    Bf_Libre(&c_buff, 0, &ltr);
    int fill = SIZE_BUFFER - ltr;
    int overlap_size = (int)(OVERLAY * WINDOW_SIZE); 


    if ((fill >= overlap_size)&& !(sg->empty)){
      // Calcular el número de datos a mantener y a reemplazar
      int new_data_size = WINDOW_SIZE - overlap_size; 

      // Mantener el xx% de los datos existentes
      for (int i = 0; i < NUM_CHANNELS; i++) {
          for (int j = 0; j < overlap_size; j++) {
              sg->wnd[i].canal[j] = sg->wnd[i].canal[j + new_data_size]; // Desplazar los datos
          }
      }

      // Llenar el yy% restante con nuevos datos
      for (int i = 0; i < NUM_CHANNELS; i++) {
          for (int j = 0; j < new_data_size; j++) {
              Bf_data input;
              Bf_Bajar_Dato(&c_buff, i, (Bf_data*)&input);
              sg->wnd[i].canal[overlap_size + j] = Fc_Procese(&c_filter, input, i);
          }
      }

      Cr_Procese(&c_car);

        // Imprimir los valores de las salidas de los 8 canales
        /*
        for (int i = 0; i < NUM_CHANNELS; i++) {
            for (int j = 0; j < WINDOW_SIZE; j++) {
                Serial.print(sg->wnd[i].canal[j]);
                Serial.print(",");
            }
            Serial.println();
        }
       */
    } else if ((fill >= WINDOW_SIZE)&&(sg->empty)){

      for (int j=0; j< WINDOW_SIZE; j++){
          for (int i = 0; i <  NUM_CHANNELS; i++){
            Bf_data input;
            Bf_Bajar_Dato(&c_buff,i, (Bf_data*)&input);
            sg->wnd[i].canal[j]=Fc_Procese (&c_filter, input, i);
          }  
      }

        sg->empty=NO;

      Cr_Procese(&c_car);

    }
};


/* ===== RUTINAS DE INTERFAZ ====== */



/* == FIN DE RUTINAS DE INTERFAZ == */

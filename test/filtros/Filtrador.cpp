/* Filtrador.c    implementaci�n del módulo de filtrado de señales */

#include "Filtrador.h"
#include "Varios.h"


/* Rutina para iniciar el módulo (su estructura de datos) */   
char Fc_Inicie (Fc_Control *fc, 
                Fc_TopNotchFilterState *tn, 
                Fc_PassBandFilterState *pb)
   {

   //inicializar estados de filtros   
   fc->tn = tn;
   fc->pb = pb;   
  
   return SI;
   };

                  
/* Rutina para procesar el módulo (dentro del loop de polling) */				
Fc_data Fc_Procese (Fc_Control *fc, Fc_data input, int canal ){

  Fc_data outputSignal;

   // Aplicar el filtro top notch 
  Fc_TopNotchFilterState *tn = fc->tn + canal;
  outputSignal= topNotch(input, tn);

   // Aplicar el filtro pasa bandas
  Fc_PassBandFilterState *pb = fc->pb + canal;
  outputSignal= pasabandas(outputSignal, pb->states);

  return outputSignal; 
   
};


   
Fc_data topNotch(Fc_data input, Fc_TopNotchFilterState* state) {
   Fc_data x = input - -1.35553798 * state->z1 - 0.85952856 * state->z2;
   Fc_data output = 0.92976428 * x + -1.35553798 * state->z1 + 0.92976428 * state->z2;

   // Actualizar los estados
   state->z2 = state->z1;
   state->z1 = x;

   return output;
}


Fc_data pasabandas(Fc_data input, Fc_FilterState* states)
{
  Fc_data output = input;

    Fc_FilterState* state = &states[0];
    Fc_data x = output - -1.57479151*state->z1 - 0.62601070*state->z2;
    output = 0.70747170*x + -1.41494340*state->z1 + 0.70747170*state->z2;
    state->z2 = state->z1;
    state->z1 = x;
  
    state = &states[1];
    x = output - -1.76898210*state->z1 - 0.82638518*state->z2;
    output = 1.00000000*x + -2.00000000*state->z1 + 1.00000000*state->z2;
    state->z2 = state->z1;
    state->z1 = x;

    state = &states[2];
    x = output - 1.97673918*state->z1 - 0.97689742*state->z2;
    output = 1.00000000*x + 2.00000000*state->z1 + 1.00000000*state->z2;
    state->z2 = state->z1;
    state->z1 = x;
  
    state = &states[3];
    x = output - 1.99022809*state->z1 - 0.99038704*state->z2;
    output = 1.00000000*x + 2.00000000*state->z1 + 1.00000000*state->z2;
    state->z2 = state->z1;
    state->z1 = x;

  return output;
}



/* ===== RUTINAS DE INTERFAZ ====== */



/* == FIN DE RUTINAS DE INTERFAZ == */

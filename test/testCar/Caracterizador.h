/* Caracterizador.h    Definiciones del m�dulo de extracción de caracteristicas */
#if !defined(CARACTERIZADOR_H)

#define  CARACTERIZADOR_H

#include "Segmentador.h"

//Estructura de control del modulo caracterizador
typedef struct Cr_Control Cr_Control;
struct Cr_Control
{               
   
   
};
   
/* ======= Rutinas ======== */
/* Rutina para iniciar el módulo (su estructura de datos) */   
char Cr_Inicie (Cr_Control *cr);
                  
/* Rutina para procesar el módulo (dentro del loop de polling) */				
void Cr_Procese (Cr_Control *cr);

/* ===== RUTINAS DE INTERFAZ ====== */
//pendiente

/* == FIN DE RUTINAS DE INTERFAZ == */

#endif
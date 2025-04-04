/* mediana.h    Definiciones del m�dulo de filtro de Mediana */
#if !defined(MEDIANA_H)

#define  MEDIANA_H

#include <model.h>

#define TAM_FIL 25 

//Estructura de control del filtro de mediana
typedef struct Md_Control Md_Control;

struct Md_Control
{                  
   /* Filtro de almacenamiento */
  volatile IA_gesture filtro[AM_FIL];
};
   
/* ======= Rutinas ======== */
/* Rutina para iniciar el módulo (su estructura de datos) */   
char Md_Inicie (Md_Control *md);
                  
/* Rutina para procesar el módulo (dentro del loop de polling) */				
void Md_Procese (Md_Control *md);

/* ===== RUTINAS DE INTERFAZ ====== */
void Md_savePrediction(Md_Control *md, IA_gesture pred);

/* == FIN DE RUTINAS DE INTERFAZ == */

#endif
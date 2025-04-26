/* mediana.c    implementaci�n del m�dulo de filtro de Mediana */

#include "median.h"
#include <display.h>
#include "Varios.h"

extern Dp_Control c_display;


/* Rutina para iniciar el módulo (su estructura de datos) */   
char Md_Inicie (Md_Control *md){
    if (md == NULL) return NO; 
    for (int i=0; i<TAM_FIL; i++) 
      md->filtro[i]=0;
  return SI;
};

                  
/* Rutina para procesar el módulo */				
IA_gesture Md_Procese (Md_Control *md){

  // Crear un arreglo local para almacenar y ordenar los datos
    IA_gesture copia[TAM_FIL];
    for (int i = 0; i < TAM_FIL; i++) {
        copia[i] = md->filtro[i];
    }

    // Ordenar el arreglo copia (algoritmo de burbuja o selección, aquí usamos un doble for simple)
    for (int i = 0; i < TAM_FIL - 1; i++) {
        for (int j = i + 1; j < TAM_FIL; j++) {
            if (copia[i] > copia[j]) {
                IA_gesture temp = copia[i];
                copia[i] = copia[j];
                copia[j] = temp;
            }
        }
    }

    // Calcular la mediana
    IA_gesture mediana;
    if (TAM_FIL % 2 == 1) {
        // Si el número de elementos es impar, la mediana es el elemento central
        mediana = copia[TAM_FIL / 2];
    } else {
        // Si el número de elementos es par, se promedian los dos valores centrales.
        // Atención: si IA_gesture es entero, el resultado también será entero.
        mediana = (copia[(TAM_FIL - 1) / 2] + copia[TAM_FIL / 2]) / 2;
    }

    return mediana;
   
};

/* ===== RUTINAS DE INTERFAZ ====== */


/* Rutina para activar un canal. Indica si se pudo activar. */
void Md_savePrediction(Md_Control *md, IA_gesture pred){
    for (int i = TAM_FIL - 1; i > 0; i--) {
        md->filtro[i] = md->filtro[i - 1];
    }
    // Insertar la nueva predicción en la posición 0
    md->filtro[0] = pred;
    IA_gesture res=Md_Procese (md);
    Dp_updatePrediction(&c_display,res);

}

/* == FIN DE RUTINAS DE INTERFAZ == */

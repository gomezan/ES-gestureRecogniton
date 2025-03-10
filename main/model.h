/* display.h    Definiciones del m�dulo Display */
#if !defined(MODEL_H)
#define  MODEL_H

#include <Tiempo.h>

#define NN 0x01  ///red neuronal
#define RF 0x02  ///random forest 

//Arena necesaria para correr el modelo
#define ARENA_SIZE 1024*6

typedef unsigned char IA_gesture;
typedef unsigned char algoritmo;

//Estructura de control del display
typedef struct IA_Control IA_Control;

struct IA_Control
{                  
   /* Escoger nombre del modelo */
   algoritmo   modelo;
   
};
   

/* ======= Rutinas ======== */ 
/* Rutina para iniciar el módulo (su estructura de datos) */   
char IA_Inicie (IA_Control *ia, algoritmo   modelo);
                  
/* Rutina para procesar el módulo (dentro del loop de polling) */				
void IA_Procese (IA_Control *ia);

/* ===== RUTINAS DE INTERFAZ ====== */
char IA_Predict(IA_Control *ia, float x[96]);

/* == FIN DE RUTINAS DE INTERFAZ == */

#endif
/* Segmentador.h    Definiciones del m�dulo que contiene la logica de la segmentación de las señales en ventanas */
#if !defined(SEGMENTADOR_H)

#define  SEGMENTADOR_H

#include <Tiempo.h>

#define PERIODO_SG 100 // Programado a 5 Hz
#define WINDOW_SIZE 10

/* Tipo de dato que almacena el tamaño de la ventana a tratar */
typedef float Sg_data;

typedef struct Sg_canalData Sg_canalData;
struct Sg_canalData{
   Sg_data canal[WINDOW_SIZE]={0}; 
};

//Estructura de control del segemntador
typedef struct Sg_Control Sg_Control;
struct Sg_Control
{               
   /* Interfaz al módulo de tiempo */
   Tm_Num   n_periodo;
  /* Ventana de segmentación */
   volatile Sg_canalData *wnd;
      
};
   
/* ======= Rutinas ======== */
/* Rutina para iniciar el módulo (su estructura de datos) */   
char Sg_Inicie (Sg_Control *sg, Tm_Num n_periodo, Sg_canalData *wnd);
                  
/* Rutina para procesar el módulo (dentro del loop de polling) */				
void Sg_Procese (Sg_Control *sg);

/* ===== RUTINAS DE INTERFAZ ====== */
//pendiente

/* == FIN DE RUTINAS DE INTERFAZ == */

#endif
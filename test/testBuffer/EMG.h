/* EMG.h    Definiciones del m�dulo de adqusición de señales */
#if !defined(EMG_H)

#define  EMG_H

#include <Tiempo.h>

#define PERIODO_BASE 1 // Programado a 500 Hz

//Definición de los pines de entrada
#define INPUT_PIN0 A0
#define INPUT_PIN1 A1
#define INPUT_PIN2 A2
#define INPUT_PIN3 A3
#define INPUT_PIN4 A4
#define INPUT_PIN5 A5
#define INPUT_PIN6 A8
#define INPUT_PIN7 A9 

const int analogPins[NUM_CHANNELS] = {INPUT_PIN0, INPUT_PIN1, INPUT_PIN2, INPUT_PIN3, INPUT_PIN4, INPUT_PIN5, INPUT_PIN6, INPUT_PIN7};

#define ORDER_PB 20

//Estructuras de almacenamiento de datos de los filtros digitales
typedef struct EMG_FilterState EMG_FilterState;
struct EMG_FilterState {
    float z1 = 0.0, z2 = 0.0;
};

typedef EMG_FilterState EMG_TopNotchFilterState;

typedef struct EMG_PassBandFilterState EMG_PassBandFilterState;
struct EMG_PassBandFilterState {
   EMG_FilterState states[ORDER_PB];  // 20 estructuras z1, z2 por canal
};

//Estructura de control del display
typedef struct EMG_Control EMG_Control;


struct EMG_Control
{               

   /* Tabla de estados top notch */
   EMG_TopNotchFilterState *tn;
   /* Tabla de estados pasa bandas */
   EMG_PassBandFilterState *pb;
   /* Interfaz al módulo de tiempo */
   Tm_Num   n_periodo;
    
   short int cont=0; 
   
   };
   
/* ======= Rutinas ======== */
/* Rutina para iniciar el módulo (su estructura de datos) */   
char EMG_Inicie (EMG_Control *emg, Tm_Num n_periodo, EMG_TopNotchFilterState *tn, EMG_PassBandFilterState *pb);
                  
/* Rutina para procesar el módulo (dentro del loop de polling) */				
void EMG_Procese (EMG_Control *emg);

/* Rutina para filtrar la señal con un filtro top notch */
float topNotch(float input, EMG_TopNotchFilterState* state);

/* Rutina para filtrar la señal con un filtro pasa bandas */
float pasabandas(float input, EMG_FilterState* states);

void inicializar_vectores();
/* ===== RUTINAS DE INTERFAZ ====== */
//pendiente

/* == FIN DE RUTINAS DE INTERFAZ == */

#endif
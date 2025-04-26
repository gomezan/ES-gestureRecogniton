/* EMG.h    Definiciones del m�dulo de adqusición de señales */
#if !defined(EMG_H)

#define  EMG_H

#include <Tiempo.h>

#define PERIODO_EMG 1 // Programado a 500 Hz

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

/* Tipo de dato que almacena el tamaño de la ventana a tratar */
typedef short EMG_data;
                  
/* Rutina para procesar el módulo (dentro del loop de polling) */				
void EMG_Procese ();


/* ===== RUTINAS DE INTERFAZ ====== */
//pendiente

/* == FIN DE RUTINAS DE INTERFAZ == */

#endif
/* Tiempo.h    Declaraciones del modulo de tiempo */
#if !defined(TIEMPO_H)

#define TIEMPO_H

#include <Varios.h>
#include <Arduino.h>

/* Tipo de dato para los contadores */
typedef unsigned int Tm_Contador;

/* Estructura para definir e implementar un período */
typedef struct Tm_Periodo Tm_Periodo;
#define SAMPLE_RATE 500         // Frecuencia de muestreo en Hz
#define TM_PER_F_ACTIVO    0x01		/* El per�odo est� activo */
#define TM_PER_F_FC        0x02		/* Hubo fin de conteo en el per�odo */
struct Tm_Periodo
   {
   unsigned char banderas;
   Tm_Contador contador,		/* Contador para calcular el per�odo */
               periodo;			/* Valor del per�odo a generar */
   };
   

/* Tipo de dato para dimensiones de los arreglos din�micos */
typedef unsigned char Tm_Num;

/* Tipo de dato de la rutina utilizada para verificar el estado de fin de conteo del timer (HW) y/o
bajar la bandera de fin de conteo del timer (HW) */


/* Estructura de control del módulo */
typedef struct Tm_Control Tm_Control;
struct Tm_Control
   {
   /* Tabla de períodos */
   Tm_Periodo *pp;
   Tm_Num nper;
   
   /* Bandera de operación base del timer*/
   char atender_flag;

   };

/* Rutina para iniciar el módulo (su estructura de datos) */   
char Tm_Inicie (Tm_Control *tcp, Tm_Periodo *pp, Tm_Num nper);
                
/* Rutina para procesar el módulo (dentro del loop de polling) */				
void Tm_Procese (Tm_Control *tcp);

/* Rutina para configrar la interrupción base */
char Tm_config_timer();

/* Rutina de interrupción del timer*/
void ARDUINO_ISR_ATTR onTimer();

/* Obtiene valor de bandera principal de tiempo*/
char get_atender_flag(Tm_Control *tcp);

/* modifica el valor de bandera principal de tiempo*/
void set_atender_flag(Tm_Control *tcp, char value);

/* ===== RUTINAS DE INTERFAZ ====== */
/* Configurar un período para que empiece a funcionar */
char Tm_Inicie_periodo (Tm_Control *tcp, Tm_Num num_periodo, Tm_Contador periodo);

/* Desactivar un período para que deje de funcionar */
void Tm_Termine_periodo (Tm_Control *tcp, Tm_Num num_periodo);

/* Verificar si hubo fin de conteo en un periodo */
char Tm_Hubo_periodo (Tm_Control *tcp, Tm_Num num_periodo);

/* Bajar la bandera de conteo en un periodo */
void Tm_Baje_periodo (Tm_Control *tcp, Tm_Num num_periodo);

/* == FIN DE RUTINAS DE INTERFAZ == */
#endif
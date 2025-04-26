/* EMG.h    Definiciones del m�dulo de adqusición de señales */
#if !defined(FILTRADOR_H)

#define  FILTRADOR_H

#define ORDER_PB 20

/* Tipo de dato que almacena el tamaño de la ventana a tratar */
typedef float Fc_data;
/* Tipo de dato del estado de los filtros*/
typedef float Fc_state;

//Estructuras de almacenamiento de datos de los filtros digitales
typedef struct Fc_FilterState Fc_FilterState;
struct Fc_FilterState {
    Fc_state z1 = 0.0, z2 = 0.0;
};

typedef Fc_FilterState Fc_TopNotchFilterState;

typedef struct Fc_PassBandFilterState Fc_PassBandFilterState;
struct Fc_PassBandFilterState {
   Fc_FilterState states[ORDER_PB];  // 20 estructuras z1, z2 por canal
};

//Estructura de control del modulo EMG
typedef struct Fc_Control Fc_Control;


struct Fc_Control
{               
   /* Tabla de estados top notch */
   Fc_TopNotchFilterState *tn;
   /* Tabla de estados pasa bandas */
   Fc_PassBandFilterState *pb;   
};
   
/* ======= Rutinas ======== */
/* Rutina para iniciar el módulo (su estructura de datos) */   
char Fc_Inicie (Fc_Control *fc, Fc_TopNotchFilterState *tn, Fc_PassBandFilterState *pb);
                  
/* Rutina para procesar el módulo (dentro del loop de polling) */				
Fc_data Fc_Procese (Fc_Control *fc, Fc_data input, int canal );

/* Rutina para filtrar la señal con un filtro top notch */
Fc_data topNotch(Fc_data input, Fc_TopNotchFilterState* state);

/* Rutina para filtrar la señal con un filtro pasa bandas */
Fc_data pasabandas(Fc_data input, Fc_FilterState* states);

/* ===== RUTINAS DE INTERFAZ ====== */
//pendiente

/* == FIN DE RUTINAS DE INTERFAZ == */

#endif
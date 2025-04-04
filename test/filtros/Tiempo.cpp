/* Tiempo.c    Implementación del modulo de tiempo */
#if !defined(TIEMPO_C)

#define TIEMPO_C

#include <Tiempo.h>

extern Tm_Control c_tiempo;

/* Rutina para iniciar el módulo (su estructura de datos) */   
char Tm_Inicie (Tm_Control *tcp,
                Tm_Periodo *pp, 
                Tm_Num nper)
   {
   /* Tabla de períodos */
   tcp->pp = pp;
   tcp->nper = nper;
   for (; nper; ++pp, --nper)
      {
      pp->banderas = 0;
      pp->contador = pp->periodo = 0;
      };
   
   /*Bajar bandera de funcionamiento base del temporizador*/
   tcp->atender_flag=NO;

   return SI;
   };

/* Rutina para inciar la configuación de la interrupción base */  
char Tm_config_timer()
{

  hw_timer_t *timer = NULL;

     // Set timer frequency to 1 Mhz
  timer = timerBegin(100000);
  // Attach onTimer function to our timer.
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, (100000 / SAMPLE_RATE), true, 0);

  return SI;
}

/* Rutina de la interrupción */		
void ARDUINO_ISR_ATTR onTimer() {
  c_tiempo.atender_flag=SI;
}

/* Rutina para procesar el módulo (dentro del loop de polling) */				
void Tm_Procese (Tm_Control *tcp){
   Tm_Num n;
   Tm_Periodo *pp;
  
   for (n = tcp->nper, pp = tcp->pp; n; ++pp, --n){
  
      if (pp->banderas & TM_PER_F_ACTIVO){
          --(pp->contador);
          if ( !(pp->contador) ){
              pp->banderas |= TM_PER_F_FC;
              pp->contador = pp->periodo;
          };
      };
    };
  };

/* Obtiene valor de bandera principal de tiempo*/
char get_atender_flag(Tm_Control *tcp){
  return tcp->atender_flag;
}

/* modifica el valor de bandera principal de tiempo*/
void set_atender_flag(Tm_Control *tcp, char value){
  tcp->atender_flag=value;
}

/* ===== RUTINAS DE INTERFAZ ====== */
/* Configurar un período para que empiece a funcionar */
char Tm_Inicie_periodo (Tm_Control *tcp, 
                        Tm_Num num_periodo,
                        Tm_Contador periodo)
   {

   Tm_Periodo *pp = tcp->pp + num_periodo;
   
   if (num_periodo >= tcp->nper){
    return NO;
   }
      
   pp->banderas = TM_PER_F_ACTIVO;
   pp->contador = pp->periodo = periodo;
   
   return SI;
   };

/* Desactivar un período para que deje de funcionar */
void Tm_Termine_periodo (Tm_Control *tcp, Tm_Num num_periodo)
   {
   Tm_Periodo *pp = tcp->pp + num_periodo;
   
   if (num_periodo >= tcp->nper)
      return;

   pp->banderas &= ~TM_PER_F_ACTIVO;
   };

/* Verificar si hubo fin de conteo en un periodo */
char Tm_Hubo_periodo (Tm_Control *tcp, Tm_Num num_periodo)
   {
   Tm_Periodo *pp = tcp->pp + num_periodo;
   
   if (num_periodo >= tcp->nper)
      return NO;

   if (pp->banderas & TM_PER_F_FC)
      return SI;
   
   return NO;
   };

/* Bajar la bandera de conteo en un periodo */
void Tm_Baje_periodo (Tm_Control *tcp, Tm_Num num_periodo)
   {
   Tm_Periodo *pp = tcp->pp + num_periodo;
   
   if (num_periodo >= tcp->nper)
      return;

   pp->banderas &= ~TM_PER_F_FC;
   };



/* == FIN DE RUTINAS DE INTERFAZ == */

#endif
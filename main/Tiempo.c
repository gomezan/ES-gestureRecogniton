/* Tiempo.c    Implementación del modulo de tiempo */
#if !defined(TIEMPO_C)

#define TIEMPO_C

#include <Tiempo.h>

hw_timer_t *timer = NULL;

/* Rutina para iniciar el módulo (su estructura de datos) */   
char Tm_Inicie (Tm_Control *tcp,
                Tm_Periodo *pp, 
                Tm_Num nper, 
                Tm_Timeout *tp, 
                Tm_Num nto)
   {
   /* Tabla de períodos */
   tcp->pp = pp;
   tcp->nper = nper;
   for (; nper; ++pp, --nper)
      {
      pp->banderas = 0;
      pp->contador = pp->periodo = 0;
      };
   
   /* Tabla de timeouts/retardos */
   tcp->tp = tp;
   tcp->nto = nto;
   for (; nto; ++tp, --nto)
      *tp = 0;
   
   /*Bajar bandera de funcionamiento base del temporizador*/
   tcp->atender_flag=NO;

   return SI;
   };

/* Rutina para inciar la configuación de la interrupción base */  
char Tm_config_timer()
{
     // Set timer frequency to 1 Mhz
  timer = timerBegin(1000000);
  // Attach onTimer function to our timer.
  timerAttachInterrupt(timer, &onTimer);
  // Set alarm to call onTimer function every second (value in microseconds).
  // Repeat the alarm (third parameter) with unlimited count = 0 (fourth parameter).
  timerAlarm(timer, (1000000 / SAMPLE_RATE), true, 0);

  return SI;
}


/* Rutina de la interrupción */		
void ARDUINO_ISR_ATTR onTimer() {
int a=0;

}

/* Rutina para procesar el módulo (dentro del loop de polling) */				
void Tm_Procese (Tm_Control *tcp)
   {
   Tm_Num n;
   Tm_Periodo *pp;
   Tm_Timeout *tp;
      
   for (n = tcp->nper, pp = tcp->pp; n; ++pp, --n)
      if (pp->banderas & TM_PER_F_ACTIVO)
         {
         --(pp->contador);
         if ( !(pp->contador) )
            {
            pp->banderas |= TM_PER_F_FC;
            pp->contador = pp->periodo;
            };
         };

   for (n = tcp->nto, tp = tcp->tp; n; ++tp, --n)
      if (*tp)
         --(*tp);
   };

/* ===== RUTINAS DE INTERFAZ ====== */
/* Configurar un período para que empiece a funcionar */
char Tm_Inicie_periodo (Tm_Control *tcp, 
                        Tm_Num num_periodo,
                        Tm_Contador periodo)
   {
   Tm_Periodo *pp = tcp->pp + num_periodo;
   
   if (num_periodo >= tcp->nper)
      return NO;
      
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

/* Configurar un timeout/retardo para que empiece a funcionar */
char Tm_Inicie_timeout (Tm_Control *tcp, Tm_Num num_timeout, Tm_Contador espera)
   {
   Tm_Timeout *tp = tcp->tp + num_timeout;
   
   if (num_timeout >= tcp->nto)
      return NO;
      
   *tp = espera;
   
   return SI;
   };

/* Desactivar un timeout/retardo para que deje de funcionar */
void Tm_Termine_timeout (Tm_Control *tcp, Tm_Num num_timeout)
   {
   Tm_Timeout *tp = tcp->tp + num_timeout;
   
   if (num_timeout >= tcp->nto)
      return;
      
   *tp = 0;
   };

/* Verificar si hubo timeout (o se completo el retardo) */
char Tm_Hubo_timeout (Tm_Control *tcp, Tm_Num num_timeout)
   {
   Tm_Timeout *tp = tcp->tp + num_timeout;
   
   if (num_timeout >= tcp->nto)
      return NO;
      
   if (*tp)
      return NO;

   return SI;
   };

/* == FIN DE RUTINAS DE INTERFAZ == */

#endif
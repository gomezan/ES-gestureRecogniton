/* Buffer.c    Implementación del modulo del Buffer */

#include "Buffer.h"
#include "driver/gpio.h"

/* ======= Rutinas ======== */

/* Rutina para iniciar el módulo (su estructura de datos) */   
void Bf_Inicie(Buffer_Control *buf, Bf_data *datos,  Bf_pointer total)
{
    buf->datos = datos;
    buf->total = total;
    buf->cont = 0;

    for(;total;--total,++datos)
        *datos = 0;
    
    buf->read = 0;
    buf->write = 0;
    buf->full = 0;
    buf->active = 1;
}

/* Rutina para verificar si el buffer está o no lleno */
char Bf_Lleno(Buffer_Control *buf)
{
    if(!(buf->active))
        return -1;

    if(buf->full)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
    
}

/* Rutina para verificar si el buffer está vacío */
char Bf_Vacio(Buffer_Control *buf)
{
    if(!(buf->active))
        return -1;

    if(buf->cont == 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


/* Rutina para subir un dato al buffer */
char Bf_Subir_Dato(Buffer_Control *buf, Bf_data write)
{
    if(!(buf->active))
        return FALSE;
    
    if(!(buf->full))
    {
        ++(buf->cont);
        (buf->datos)[buf->write] = write;
        if(buf->write < (buf->total-1))
        {
            ++(buf->write);
        }
        else
        {
            buf->write = 0;
        }
        if(buf->write == buf->read)
            buf->full = 1;

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/* Rutina para bajar un dato del buffer */
char Bf_Bajar_Dato(Buffer_Control *buf, Bf_data *read)
{
    if(!(buf->active))
        return FALSE;

    Bf_pointer free = 0;

    // Se revisa si hay datos en el buffer
    // Como el contador lleva los datos adentro del buffer, si es mayor que 0, hay al menos un dato
    if(buf->cont > 0)
    {
        (*read) = (buf->datos)[buf->read];
        if(buf->read < (buf->total-1))
        {
            ++(buf->read);
        }
        else
        {
            buf->read = 0;
        }
        --(buf->cont);
        buf->full = 0;

    //printf("bajar dato: %d",buf->cont);
        return TRUE;
    }

    //printf("bajar dato: %d",buf->cont);
    return FALSE;
}

/* Rutina para verificar cuantos espacios tiene libres */
char Bf_Libre(Buffer_Control *buf, Bf_pointer *free)
{
    if(!(buf->active))
        return FALSE;

    (*free) = buf->total - buf->cont;
    
    return TRUE;
}

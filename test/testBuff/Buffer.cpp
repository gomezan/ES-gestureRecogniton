/* Buffer.c - Implementación del módulo del Buffer para 8 canales */
#include "Buffer.h"

void Bf_Inicie(Buffer_Control *buf, Bf_pointer total) {
    buf->total = total;
    buf->active = 1;
    for (int ch = 0; ch < NUM_CHANNELS; ch++) {
        buf->cont[ch] = 0;
        buf->read[ch] = 0;
        buf->write[ch] = 0;
        buf->full[ch] = 0;
        for (int i = 0; i < total; i++) {
            buf->datos[ch][i] = 0;
        }
    }
}

char Bf_Lleno(Buffer_Control *buf, int channel) {
    if (!buf->active) return -1;
    return buf->full[channel];
}

char Bf_Vacio(Buffer_Control *buf, int channel) {
    if (!buf->active) return -1;
    return (buf->cont[channel] == 0);
}

char Bf_Subir_Dato(Buffer_Control *buf, int channel, Bf_data write) {
    if (!buf->active) return FALSE;
    if (!buf->full[channel]) {
        buf->datos[channel][buf->write[channel]] = write;
        buf->write[channel] = (buf->write[channel] + 1) % buf->total;
        buf->cont[channel]++;
        if (buf->write[channel] == buf->read[channel])
            buf->full[channel] = 1;
        return TRUE;
    }
    return FALSE;
}

char Bf_Bajar_Dato(Buffer_Control *buf, int channel, Bf_data *read) {
    if (!buf->active) return FALSE;
    if (buf->cont[channel] > 0) {
        *read = buf->datos[channel][buf->read[channel]];
        buf->read[channel] = (buf->read[channel] + 1) % buf->total;
        buf->cont[channel]--;
        buf->full[channel] = 0;
        return TRUE;
    }
    return FALSE;
}

char Bf_Libre(Buffer_Control *buf, int channel, Bf_pointer *free) {
    if (!buf->active) return FALSE;
    *free = buf->total - buf->cont[channel];
    return TRUE;
}
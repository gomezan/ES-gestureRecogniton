/* Caracterizador.c    implementaci�n del módulo de extracción de caracteristicas */

#include <Caracterizador.h>
#include "Varios.h"


/* Rutina para iniciar el módulo (su estructura de datos) */   
char Cr_Inicie (Cr_Control *cr,
                Sg_canalData *wnd,
                Cr_Caracteristicas *vec
                )
   {

    //Inicializar ventana
    cr->wnd=wnd;
    //Inicializar vector de caracteristicas
    cr->vec=vec;    
    
    //Inicializar funciones
    cr->funciones[0] = rms;
    cr->funciones[1] = desviacion_estandar;
    cr->funciones[2] = varianza;
    cr->funciones[3] = MAV;
    cr->funciones[4] = WL;
    cr->funciones[5] = promedio;
    cr->funciones[6] = ZC;
    cr->funciones[7] = kurtosis;
    cr->funciones[8] = skewness;
    cr->funciones[9] = integrar;
    cr->funciones[10] = SSC;

   return SI;
   };


                  
/* Rutina para procesar el módulo (dentro del loop de polling) */				
void Cr_Procese (Cr_Control *cr){

  int index = 0; // Índice para almacenar características

    for (int ch = 0; ch < NUM_CHANNELS; ch++) { // Iterar sobre canales
        for (int f_idx = 0; f_idx < NUM_CAR; f_idx++) { // Iterar sobre funciones
            cr->vec[index++] = cr->funciones[f_idx](const_cast<Cr_Caracteristicas*>(cr->wnd[ch].canal), WINDOW_SIZE);
        }
    } 
};

/* ===== Cacteristicas del vector ====== */

// Función para sumar los elementos de un array
Cr_Caracteristicas suma(const Cr_Caracteristicas* arr, int size) {
    Cr_Caracteristicas sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// Función para calcular RMS (Root Mean Square)
Cr_Caracteristicas rms(const Cr_Caracteristicas* arr, int size) {
    if (size == 0) return 0;

    Cr_Caracteristicas sum_sq = 0;
    for (int i = 0; i < size; i++) {
        sum_sq += arr[i] * arr[i]; // Elevar al cuadrado y acumular
    }

    return sqrt(sum_sq / size); // Raíz cuadrada de la media de los cuadrados
}

// Función que calcula la varianza
Cr_Caracteristicas varianza(const Cr_Caracteristicas* arr, int size) {
    if (size == 0) return 0;

    Cr_Caracteristicas mu = promedio(arr, size);
    Cr_Caracteristicas sum_sq_diff = 0;

    for (int i = 0; i < size; i++) {
        sum_sq_diff += (arr[i] - mu) * (arr[i] - mu);
    }

    return sum_sq_diff / size; // Varianza
}

// Función que calcula la desviación Estándar
Cr_Caracteristicas desviacion_estandar(const Cr_Caracteristicas* arr, int size) {
    return sqrt(varianza(arr, size)); // Desviación estándar es la raíz de la varianza
}

// Función para calcular el MAV (Mean Absolute Value)
Cr_Caracteristicas MAV(const Cr_Caracteristicas* arr, int size) {
    if (size == 0) return 0;

    Cr_Caracteristicas sum_abs = 0;
    for (int i = 0; i < size; i++) {
        sum_abs += fabs(arr[i]); // Valor absoluto
    }

    return sum_abs / size;
}

// Función para calcular el WL (Waveform Length)
Cr_Caracteristicas WL(const Cr_Caracteristicas* arr, int size) {
    if (size < 2) return 0; // No hay diferencias si hay solo un dato

    Cr_Caracteristicas wl_sum = 0;
    for (int i = 0; i < size - 1; i++) {
        wl_sum += fabs(arr[i + 1] - arr[i]); // Diferencia absoluta
    }

    return wl_sum;
}

// Función para calcular el promedio
Cr_Caracteristicas promedio(const Cr_Caracteristicas* arr, int size) {
    return (size == 0) ? 0 : suma(arr, size) / size;
} 

// Función para calcular el ZC (Zero Crossing)
Cr_Caracteristicas ZC(const Cr_Caracteristicas* arr, int size) {
    if (size < 2) return 0;

    int count = 0;
    for (int i = 1; i < size; i++) {
        if ((arr[i - 1] > 0 && arr[i] < 0) || (arr[i - 1] < 0 && arr[i] > 0)) {
            count++;
        }
    }

    return count;
}

// Función para calcular el SSC (Slope Sign Change)
Cr_Caracteristicas SSC(const Cr_Caracteristicas* arr, int size) {
    if (size < 2) return 0;

    int sign_changes = 0;
    int prev_sign = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            if (prev_sign > 0) {
                sign_changes++;
            }
            prev_sign = -1;
        } else if (arr[i] > 0) {
            if (prev_sign < 0) {
                sign_changes++;
            }
            prev_sign = 1;
        }
    }

    return sign_changes;
}


//  Función para calcular el Skewness (asimetría)
Cr_Caracteristicas skewness(const Cr_Caracteristicas* arr, int size) {
    if (size < 2) return 0.0;

    Cr_Caracteristicas mean = 0.0;
    Cr_Caracteristicas m2 = 0.0;
    Cr_Caracteristicas m3 = 0.0;

    for (int i = 0; i < size; ++i) {
        Cr_Caracteristicas delta = arr[i] - mean;
        Cr_Caracteristicas delta_n = delta / (i + 1);
        Cr_Caracteristicas term1 = delta * delta_n * i;
        mean += delta_n;
        m3 += term1 * delta_n * (i - 1) - 3 * delta_n * m2;
        m2 += term1;
    }

    if (m2 == 0.0) return 0.0;

    Cr_Caracteristicas s = std::sqrt(m2 / (size - 1));
    return (m3 / size) / (s * s * s);
}

//  Función para calcular la Kurtosis (curtosis)
Cr_Caracteristicas kurtosis(const Cr_Caracteristicas* arr, int size) {
    if (size < 2) return 0.0;

    Cr_Caracteristicas mean = 0.0;
    Cr_Caracteristicas m2 = 0.0;
    Cr_Caracteristicas m3 = 0.0; 
    Cr_Caracteristicas m4 = 0.0; 

    for (int i = 0; i < size; ++i) {
        Cr_Caracteristicas delta = arr[i] - mean;
        Cr_Caracteristicas delta_n = delta / (i + 1);
        Cr_Caracteristicas term1 = delta * delta_n * i;
        mean += delta_n;
        m3 += term1 * delta_n * (i - 1) - 3 * delta_n * m2;
        m4 += term1 * delta_n * delta_n * (i * i - 3 * i + 3) + 6 * delta_n * delta_n * m2 - 4 * delta_n * m3;
        m2 += term1;
    }

    if (m2 == 0.0) return 0.0;

    return (m4 * size) / (m2 * m2) - 3.0; //Kurtosis de Fisher
}

// Función para calcular la integral de la señal usando el método del trapecio
Cr_Caracteristicas integrar(const Cr_Caracteristicas* arr, int size) {
    Cr_Caracteristicas area = 0.0;
    Cr_Caracteristicas dx=1.0;
    for (int i = 0; i < size - 1; ++i) {
        area += 0.5 * (arr[i] + arr[i + 1]) * dx;
    }
    return area;
}


/* ===== RUTINAS DE INTERFAZ ====== */



/* == FIN DE RUTINAS DE INTERFAZ == */

/* Caracterizador.c    implementaci�n del módulo de extracción de caracteristicas */

#include <Caracterizador.h>
#include "Varios.h"


char Cr_Inicie(Cr_Control *cr, Sg_canalData *wnd, Cr_Caracteristicas *vec) {
    cr->wnd = wnd;
    cr->vec = vec;

    cr->funciones[0][0] = Cr_CrearFuncion(RMS, 0.0380157638850652, 467.3821676197466104);
        cr->funciones[1][0] = Cr_CrearFuncion(RMS, 5.3916707780954214, 359.6012505440169775);
        cr->funciones[2][0] = Cr_CrearFuncion(RMS, 0.0033569186161588, 689.3975006170871893);
        cr->funciones[3][0] = Cr_CrearFuncion(RMS, 10.1197107424910993, 938.2479806079644504);
        cr->funciones[4][0] = Cr_CrearFuncion(RMS, 7.1900358335505468, 1087.8723795586010965);
        cr->funciones[5][0] = Cr_CrearFuncion(RMS, 0.0391189639848628, 1084.1388323450107691);
        cr->funciones[6][0] = Cr_CrearFuncion(RMS, 0.1399013676249442, 1157.7550033289351177);
        cr->funciones[7][0] = Cr_CrearFuncion(RMS, 0.0405365180076148, 1003.0867144580033710);
        cr->funciones[0][1] = Cr_CrearFuncion(STD, 0.0380110243421893, 467.3559716946747926);
        cr->funciones[1][1] = Cr_CrearFuncion(STD, 5.3915321325716228, 359.6006662473003530);
        cr->funciones[2][1] = Cr_CrearFuncion(STD, 0.0033565130158372, 689.3833278782722118);
        cr->funciones[3][1] = Cr_CrearFuncion(STD, 10.1192311600775966, 937.9667394730088290);
        cr->funciones[4][1] = Cr_CrearFuncion(STD, 7.1896190599402399, 1087.7737821145015005);
        cr->funciones[5][1] = Cr_CrearFuncion(STD, 0.0390988280110037, 1083.9343730001644417);
        cr->funciones[6][1] = Cr_CrearFuncion(STD, 0.1398820409674704, 1157.7482240953891051);
        cr->funciones[7][1] = Cr_CrearFuncion(STD, 0.0405309062711781, 1003.0457528817183857);
        cr->funciones[0][2] = Cr_CrearFuncion(Varianza, 0.0014448379715425, 218421.6042786736798007);
        cr->funciones[1][2] = Cr_CrearFuncion(Varianza, 29.0686187365523026, 129312.6391655023180647);
        cr->funciones[2][2] = Cr_CrearFuncion(Varianza, 0.0000112661796255, 475249.3727565212757327);
        cr->funciones[3][2] = Cr_CrearFuncion(Varianza, 102.3988392710853645, 879781.6043576274532825);
        cr->funciones[4][2] = Cr_CrearFuncion(Varianza, 51.6906222270559752, 1183251.8010556877125055);
        cr->funciones[5][2] = Cr_CrearFuncion(Varianza, 0.0015287183518340, 1174913.7249712597113103);
        cr->funciones[6][2] = Cr_CrearFuncion(Varianza, 0.0195669853852250, 1340380.9503960271831602);
        cr->funciones[7][2] = Cr_CrearFuncion(Varianza, 0.0016427543631630, 1006100.7823740531457588);
        cr->funciones[0][3] = Cr_CrearFuncion(MAV, 0.0334222599914291, 395.7445301264584145);
        cr->funciones[1][3] = Cr_CrearFuncion(MAV, 4.1311097321445009, 291.9571220625174988);
        cr->funciones[2][3] = Cr_CrearFuncion(MAV, 0.0029242985152203, 534.6184842970219506);
        cr->funciones[3][3] = Cr_CrearFuncion(MAV, 7.9201104886389260, 785.8234524640337213);
        cr->funciones[4][3] = Cr_CrearFuncion(MAV, 5.0561411876202378, 865.0762430883910383);
        cr->funciones[5][3] = Cr_CrearFuncion(MAV, 0.0318427636907003, 842.1513125972486478);
        cr->funciones[6][3] = Cr_CrearFuncion(MAV, 0.1207054539933775, 880.2506060805848165);
        cr->funciones[7][3] = Cr_CrearFuncion(MAV, 0.0355684596589490, 815.6979886430636952);
        cr->funciones[0][4] = Cr_CrearFuncion(WL, 6.5644444741290799, 55682.6880945506563876);
        cr->funciones[1][4] = Cr_CrearFuncion(WL, 541.4729254925838404, 45347.9286915119228070);
        cr->funciones[2][4] = Cr_CrearFuncion(WL, 0.4586833890333783, 62271.1308118147935602);
        cr->funciones[3][4] = Cr_CrearFuncion(WL, 1110.0301724970609030, 113627.8052920474729035);
        cr->funciones[4][4] = Cr_CrearFuncion(WL, 805.1844282632732757, 138187.7730648851429578);
        cr->funciones[5][4] = Cr_CrearFuncion(WL, 6.1587876873679992, 103638.8377840595203452);
        cr->funciones[6][4] = Cr_CrearFuncion(WL, 23.6631861170839315, 129113.6616642828448676);
        cr->funciones[7][4] = Cr_CrearFuncion(WL, 6.9794991445949570, 135978.8389005836797878);
        cr->funciones[0][5] = Cr_CrearFuncion(Promedio, -34.0814742083912634, 33.1052897078743413);
        cr->funciones[1][5] = Cr_CrearFuncion(Promedio, -14.4210813226712844, 11.6153170914179515);
        cr->funciones[2][5] = Cr_CrearFuncion(Promedio, -36.0803851081781985, 34.0868225922039869);
        cr->funciones[3][5] = Cr_CrearFuncion(Promedio, -45.7277302166717874, 38.7952288657816453);
        cr->funciones[4][5] = Cr_CrearFuncion(Promedio, -22.3546311214303017, 23.4158201286864127);
        cr->funciones[5][5] = Cr_CrearFuncion(Promedio, -62.0156817196770831, 54.4040499404158595);
        cr->funciones[6][5] = Cr_CrearFuncion(Promedio, -74.4430298522780021, 56.8561533965116723);
        cr->funciones[7][5] = Cr_CrearFuncion(Promedio, -33.7629877797797775, 40.2054252433497936);
        cr->funciones[0][6] = Cr_CrearFuncion(ZC, 10.0000000000000000, 99.0000000000000000);
        cr->funciones[1][6] = Cr_CrearFuncion(ZC, 13.0000000000000000, 83.0000000000000000);
        cr->funciones[2][6] = Cr_CrearFuncion(ZC, 9.0000000000000000, 99.0000000000000000);
        cr->funciones[3][6] = Cr_CrearFuncion(ZC, 9.0000000000000000, 91.0000000000000000);
        cr->funciones[4][6] = Cr_CrearFuncion(ZC, 14.0000000000000000, 91.0000000000000000);
        cr->funciones[5][6] = Cr_CrearFuncion(ZC, 9.0000000000000000, 99.0000000000000000);
        cr->funciones[6][6] = Cr_CrearFuncion(ZC, 10.0000000000000000, 99.0000000000000000);
        cr->funciones[7][6] = Cr_CrearFuncion(ZC, 11.0000000000000000, 99.0000000000000000);
        cr->funciones[0][7] = Cr_CrearFuncion(kurtosis, -1.9863222456777987, 37.3440814957047067);
        cr->funciones[1][7] = Cr_CrearFuncion(kurtosis, -1.1860137100071722, 82.2649951955910694);
        cr->funciones[2][7] = Cr_CrearFuncion(kurtosis, -1.9889582568097119, 70.1129395438810121);
        cr->funciones[3][7] = Cr_CrearFuncion(kurtosis, -1.3871218493503026, 70.3993748693595478);
        cr->funciones[4][7] = Cr_CrearFuncion(kurtosis, -1.5403968348666914, 70.1419856451668124);
        cr->funciones[5][7] = Cr_CrearFuncion(kurtosis, -1.9859837323986649, 82.9621977328555431);
        cr->funciones[6][7] = Cr_CrearFuncion(kurtosis, -1.9817790875162491, 90.1783739685893835);
        cr->funciones[7][7] = Cr_CrearFuncion(kurtosis, -1.9789339995081401, 88.3452682312554316);
        cr->funciones[0][8] = Cr_CrearFuncion(skewness, -3.2162712292690401, 4.9187105543699596);
        cr->funciones[1][8] = Cr_CrearFuncion(skewness, -6.8200997944648396, 8.8466922977008160);
        cr->funciones[2][8] = Cr_CrearFuncion(skewness, -7.8947545951659777, 7.2862134061642223);
        cr->funciones[3][8] = Cr_CrearFuncion(skewness, -7.6652106783009817, 7.8837651818651695);
        cr->funciones[4][8] = Cr_CrearFuncion(skewness, -7.8530425704857008, 7.3819555175608800);
        cr->funciones[5][8] = Cr_CrearFuncion(skewness, -6.1129939427169804, 8.9170241272339563);
        cr->funciones[6][8] = Cr_CrearFuncion(skewness, -9.4902571593379115, 5.4442614654727350);
        cr->funciones[7][8] = Cr_CrearFuncion(skewness, -9.3262550589051472, 7.8261073058462571);
        cr->funciones[0][9] = Cr_CrearFuncion(iEMG, -3565.7523982924681150, 3010.0600490780461769);
        cr->funciones[1][9] = Cr_CrearFuncion(iEMG, -1500.9145027741310514, 1197.7252983398063861);
        cr->funciones[2][9] = Cr_CrearFuncion(iEMG, -3539.7147712973637681, 3110.7433968026739421);
        cr->funciones[3][9] = Cr_CrearFuncion(iEMG, -4217.6256802436282669, 3357.7982487642707383);
        cr->funciones[4][9] = Cr_CrearFuncion(iEMG, -2244.0518432668391142, 2582.3296629548167402);
        cr->funciones[5][9] = Cr_CrearFuncion(iEMG, -6005.6849099681594453, 5519.5407740847476816);
        cr->funciones[6][9] = Cr_CrearFuncion(iEMG, -8096.0266785280673503, 5392.2298324425592000);
        cr->funciones[7][9] = Cr_CrearFuncion(iEMG, -3284.3014592292879570, 3290.6943947021177337);
        cr->funciones[0][10] = Cr_CrearFuncion(SSC, 10.0000000000000000, 99.0000000000000000);
        cr->funciones[1][10] = Cr_CrearFuncion(SSC, 13.0000000000000000, 83.0000000000000000);
        cr->funciones[2][10] = Cr_CrearFuncion(SSC, 9.0000000000000000, 99.0000000000000000);
        cr->funciones[3][10] = Cr_CrearFuncion(SSC, 9.0000000000000000, 91.0000000000000000);
        cr->funciones[4][10] = Cr_CrearFuncion(SSC, 14.0000000000000000, 91.0000000000000000);
        cr->funciones[5][10] = Cr_CrearFuncion(SSC, 9.0000000000000000, 99.0000000000000000);
        cr->funciones[6][10] = Cr_CrearFuncion(SSC, 10.0000000000000000, 99.0000000000000000);
        cr->funciones[7][10] = Cr_CrearFuncion(SSC, 11.0000000000000000, 99.0000000000000000);
        cr->funciones[0][11] = Cr_CrearFuncion(WAMP, 0.0000000000000000, 95.0000000000000000);
        cr->funciones[1][11] = Cr_CrearFuncion(WAMP, 0.0000000000000000, 92.0000000000000000);
        cr->funciones[2][11] = Cr_CrearFuncion(WAMP, 0.0000000000000000, 90.0000000000000000);
        cr->funciones[3][11] = Cr_CrearFuncion(WAMP, 0.0000000000000000, 94.0000000000000000);
        cr->funciones[4][11] = Cr_CrearFuncion(WAMP, 0.0000000000000000, 99.0000000000000000);
        cr->funciones[5][11] = Cr_CrearFuncion(WAMP, 0.0000000000000000, 97.0000000000000000);
        cr->funciones[6][11] = Cr_CrearFuncion(WAMP, 0.0000000000000000, 96.0000000000000000);
        cr->funciones[7][11] = Cr_CrearFuncion(WAMP, 0.0000000000000000, 94.0000000000000000);

    return 1;
}

void Cr_Procese(Cr_Control *cr) {
    int index = 0;
    for (int ch = 0; ch < NUM_CHANNELS; ch++) {
        for (int f_idx = 0; f_idx < NUM_CAR; f_idx++) {
            Cr_FuncionCaracteristica fc = cr->funciones[ch][f_idx];
            Cr_Caracteristicas val = fc.func((const Cr_Caracteristicas*) cr->wnd[ch].canal, WINDOW_SIZE);
            if (fc.max != fc.min) {
                val = (val - fc.min) / (fc.max - fc.min);
                if (val < 0.0) val = 0.0;
                if (val > 1.0) val = 1.0;
            } else {
                val = 0.0;
            }
            cr->vec[index++] = val;
        }
    }
}


   
Cr_FuncionCaracteristica Cr_CrearFuncion(Cr_Caracteristicas (*f)(const Cr_Caracteristicas*, int), Cr_Caracteristicas min, Cr_Caracteristicas max) {
    Cr_FuncionCaracteristica fc;
    fc.func = f;
    fc.min = min;
    fc.max = max;
    return fc;
}

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
Cr_Caracteristicas RMS(const Cr_Caracteristicas* arr, int size) {
    if (size == 0) return 0;

    Cr_Caracteristicas sum_sq = 0;
    for (int i = 0; i < size; i++) {
        sum_sq += arr[i] * arr[i]; // Elevar al cuadrado y acumular
    }

    return sqrt(sum_sq / size); // Raíz cuadrada de la media de los cuadrados
}

// Función que calcula la varianza
Cr_Caracteristicas Varianza(const Cr_Caracteristicas* arr, int size) {
    if (size == 0) return 0;

    Cr_Caracteristicas mu = Promedio(arr, size);
    Cr_Caracteristicas sum_sq_diff = 0;

    for (int i = 0; i < size; i++) {
        sum_sq_diff += (arr[i] - mu) * (arr[i] - mu);
    }

    return sum_sq_diff / size; // Varianza
}

// Función que calcula la desviación Estándar
Cr_Caracteristicas STD(const Cr_Caracteristicas* arr, int size) {
    return sqrt(Varianza(arr, size)); // Desviación estándar es la raíz de la varianza
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
Cr_Caracteristicas Promedio(const Cr_Caracteristicas* arr, int size) {
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
Cr_Caracteristicas iEMG(const Cr_Caracteristicas* arr, int size) {
    Cr_Caracteristicas area = 0.0;
    Cr_Caracteristicas dx=1.0;
    for (int i = 0; i < size - 1; ++i) {
        area += 0.5 * (arr[i] + arr[i + 1]) * dx;
    }
    return area;
}


// Función para medir WAMP (Willison Amplitude)
Cr_Caracteristicas WAMP(const Cr_Caracteristicas* arr, int size) {
    if (size < 2) return 0;

    int wa = 0;
    for (int i = 1; i < size; i++) {
        if (fabs(arr[i] - arr[i - 1]) > WAMP_THRESHOLD) {
            wa++;
        }
    }

    return wa;
}

/* ===== RUTINAS DE INTERFAZ ====== */



/* == FIN DE RUTINAS DE INTERFAZ == */


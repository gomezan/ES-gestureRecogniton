/* Caracterizador.c    implementaci�n del módulo de extracción de caracteristicas */

#include <Caracterizador.h>
#include "Varios.h"
#include "model.h"
#include "arduinoFFT.h"

extern IA_Control c_modelo;

char Cr_Inicie (Cr_Control *cr,
                Sg_canalData *wnd,
                Cr_Caracteristicas *vec
                )
{
    
    /*Estructura de datos*/
    cr->wnd = wnd;
    cr->vec = vec;
    
      // caracteristicas en el dominio del tiempo
       //[canal][caracteristica] 
        cr->funcionesTime[0][0] = Cr_CrearFuncion_time(RMS, 0.0380157638850652, 467.3821676197466104);
        cr->funcionesTime[1][0] = Cr_CrearFuncion_time(RMS, 5.3916707780954214, 359.6012505440169775);
        cr->funcionesTime[2][0] = Cr_CrearFuncion_time(RMS, 0.0033569186161588, 689.3975006170871893);
        cr->funcionesTime[3][0] = Cr_CrearFuncion_time(RMS, 10.1197107424910993, 938.2479806079644504);
        cr->funcionesTime[4][0] = Cr_CrearFuncion_time(RMS, 7.1900358335505468, 1087.8723795586010965);
        cr->funcionesTime[5][0] = Cr_CrearFuncion_time(RMS, 0.0391189639848628, 1084.1388323450107691);
        cr->funcionesTime[6][0] = Cr_CrearFuncion_time(RMS, 0.1399013676249442, 1157.7550033289351177);
        cr->funcionesTime[7][0] = Cr_CrearFuncion_time(RMS, 0.0405365180076148, 1003.0867144580033710);
        cr->funcionesTime[0][1] = Cr_CrearFuncion_time(STD, 0.0380110243421893, 467.3559716946747926);
        cr->funcionesTime[1][1] = Cr_CrearFuncion_time(STD, 5.3915321325716228, 359.6006662473003530);
        cr->funcionesTime[2][1] = Cr_CrearFuncion_time(STD, 0.0033565130158372, 689.3833278782722118);
        cr->funcionesTime[3][1] = Cr_CrearFuncion_time(STD, 10.1192311600775966, 937.9667394730088290);
        cr->funcionesTime[4][1] = Cr_CrearFuncion_time(STD, 7.1896190599402399, 1087.7737821145015005);
        cr->funcionesTime[5][1] = Cr_CrearFuncion_time(STD, 0.0390988280110037, 1083.9343730001644417);
        cr->funcionesTime[6][1] = Cr_CrearFuncion_time(STD, 0.1398820409674704, 1157.7482240953891051);
        cr->funcionesTime[7][1] = Cr_CrearFuncion_time(STD, 0.0405309062711781, 1003.0457528817183857);
        cr->funcionesTime[0][2] = Cr_CrearFuncion_time(Varianza, 0.0014448379715425, 218421.6042786736798007);
        cr->funcionesTime[1][2] = Cr_CrearFuncion_time(Varianza, 29.0686187365523026, 129312.6391655023180647);
        cr->funcionesTime[2][2] = Cr_CrearFuncion_time(Varianza, 0.0000112661796255, 475249.3727565212757327);
        cr->funcionesTime[3][2] = Cr_CrearFuncion_time(Varianza, 102.3988392710853645, 879781.6043576274532825);
        cr->funcionesTime[4][2] = Cr_CrearFuncion_time(Varianza, 51.6906222270559752, 1183251.8010556877125055);
        cr->funcionesTime[5][2] = Cr_CrearFuncion_time(Varianza, 0.0015287183518340, 1174913.7249712597113103);
        cr->funcionesTime[6][2] = Cr_CrearFuncion_time(Varianza, 0.0195669853852250, 1340380.9503960271831602);
        cr->funcionesTime[7][2] = Cr_CrearFuncion_time(Varianza, 0.0016427543631630, 1006100.7823740531457588);
        cr->funcionesTime[0][3] = Cr_CrearFuncion_time(MAV, 0.0334222599914291, 395.7445301264584145);
        cr->funcionesTime[1][3] = Cr_CrearFuncion_time(MAV, 4.1311097321445009, 291.9571220625174988);
        cr->funcionesTime[2][3] = Cr_CrearFuncion_time(MAV, 0.0029242985152203, 534.6184842970219506);
        cr->funcionesTime[3][3] = Cr_CrearFuncion_time(MAV, 7.9201104886389260, 785.8234524640337213);
        cr->funcionesTime[4][3] = Cr_CrearFuncion_time(MAV, 5.0561411876202378, 865.0762430883910383);
        cr->funcionesTime[5][3] = Cr_CrearFuncion_time(MAV, 0.0318427636907003, 842.1513125972486478);
        cr->funcionesTime[6][3] = Cr_CrearFuncion_time(MAV, 0.1207054539933775, 880.2506060805848165);
        cr->funcionesTime[7][3] = Cr_CrearFuncion_time(MAV, 0.0355684596589490, 815.6979886430636952);
        cr->funcionesTime[0][4] = Cr_CrearFuncion_time(WL, 6.5644444741290799, 55682.6880945506563876);
        cr->funcionesTime[1][4] = Cr_CrearFuncion_time(WL, 541.4729254925838404, 45347.9286915119228070);
        cr->funcionesTime[2][4] = Cr_CrearFuncion_time(WL, 0.4586833890333783, 62271.1308118147935602);
        cr->funcionesTime[3][4] = Cr_CrearFuncion_time(WL, 1110.0301724970609030, 113627.8052920474729035);
        cr->funcionesTime[4][4] = Cr_CrearFuncion_time(WL, 805.1844282632732757, 138187.7730648851429578);
        cr->funcionesTime[5][4] = Cr_CrearFuncion_time(WL, 6.1587876873679992, 103638.8377840595203452);
        cr->funcionesTime[6][4] = Cr_CrearFuncion_time(WL, 23.6631861170839315, 129113.6616642828448676);
        cr->funcionesTime[7][4] = Cr_CrearFuncion_time(WL, 6.9794991445949570, 135978.8389005836797878);
        cr->funcionesTime[0][5] = Cr_CrearFuncion_time(Promedio, -34.0814742083912634, 33.1052897078743413);
        cr->funcionesTime[1][5] = Cr_CrearFuncion_time(Promedio, -14.4210813226712844, 11.6153170914179515);
        cr->funcionesTime[2][5] = Cr_CrearFuncion_time(Promedio, -36.0803851081781985, 34.0868225922039869);
        cr->funcionesTime[3][5] = Cr_CrearFuncion_time(Promedio, -45.7277302166717874, 38.7952288657816453);
        cr->funcionesTime[4][5] = Cr_CrearFuncion_time(Promedio, -22.3546311214303017, 23.4158201286864127);
        cr->funcionesTime[5][5] = Cr_CrearFuncion_time(Promedio, -62.0156817196770831, 54.4040499404158595);
        cr->funcionesTime[6][5] = Cr_CrearFuncion_time(Promedio, -74.4430298522780021, 56.8561533965116723);
        cr->funcionesTime[7][5] = Cr_CrearFuncion_time(Promedio, -33.7629877797797775, 40.2054252433497936);
        cr->funcionesTime[0][6] = Cr_CrearFuncion_time(ZC, 10.0000000000000000, 99.0000000000000000);
        cr->funcionesTime[1][6] = Cr_CrearFuncion_time(ZC, 13.0000000000000000, 83.0000000000000000);
        cr->funcionesTime[2][6] = Cr_CrearFuncion_time(ZC, 9.0000000000000000, 99.0000000000000000);
        cr->funcionesTime[3][6] = Cr_CrearFuncion_time(ZC, 9.0000000000000000, 91.0000000000000000);
        cr->funcionesTime[4][6] = Cr_CrearFuncion_time(ZC, 14.0000000000000000, 91.0000000000000000);
        cr->funcionesTime[5][6] = Cr_CrearFuncion_time(ZC, 9.0000000000000000, 99.0000000000000000);
        cr->funcionesTime[6][6] = Cr_CrearFuncion_time(ZC, 10.0000000000000000, 99.0000000000000000);
        cr->funcionesTime[7][6] = Cr_CrearFuncion_time(ZC, 11.0000000000000000, 99.0000000000000000);
        cr->funcionesTime[0][7] = Cr_CrearFuncion_time(kurtosis, -1.9863222456777987, 37.3440814957047067);
        cr->funcionesTime[1][7] = Cr_CrearFuncion_time(kurtosis, -1.1860137100071722, 82.2649951955910694);
        cr->funcionesTime[2][7] = Cr_CrearFuncion_time(kurtosis, -1.9889582568097119, 70.1129395438810121);
        cr->funcionesTime[3][7] = Cr_CrearFuncion_time(kurtosis, -1.3871218493503026, 70.3993748693595478);
        cr->funcionesTime[4][7] = Cr_CrearFuncion_time(kurtosis, -1.5403968348666914, 70.1419856451668124);
        cr->funcionesTime[5][7] = Cr_CrearFuncion_time(kurtosis, -1.9859837323986649, 82.9621977328555431);
        cr->funcionesTime[6][7] = Cr_CrearFuncion_time(kurtosis, -1.9817790875162491, 90.1783739685893835);
        cr->funcionesTime[7][7] = Cr_CrearFuncion_time(kurtosis, -1.9789339995081401, 88.3452682312554316);
        cr->funcionesTime[0][8] = Cr_CrearFuncion_time(skewness, -3.2162712292690401, 4.9187105543699596);
        cr->funcionesTime[1][8] = Cr_CrearFuncion_time(skewness, -6.8200997944648396, 8.8466922977008160);
        cr->funcionesTime[2][8] = Cr_CrearFuncion_time(skewness, -7.8947545951659777, 7.2862134061642223);
        cr->funcionesTime[3][8] = Cr_CrearFuncion_time(skewness, -7.6652106783009817, 7.8837651818651695);
        cr->funcionesTime[4][8] = Cr_CrearFuncion_time(skewness, -7.8530425704857008, 7.3819555175608800);
        cr->funcionesTime[5][8] = Cr_CrearFuncion_time(skewness, -6.1129939427169804, 8.9170241272339563);
        cr->funcionesTime[6][8] = Cr_CrearFuncion_time(skewness, -9.4902571593379115, 5.4442614654727350);
        cr->funcionesTime[7][8] = Cr_CrearFuncion_time(skewness, -9.3262550589051472, 7.8261073058462571);
        cr->funcionesTime[0][9] = Cr_CrearFuncion_time(iEMG, -3565.7523982924681150, 3010.0600490780461769);
        cr->funcionesTime[1][9] = Cr_CrearFuncion_time(iEMG, -1500.9145027741310514, 1197.7252983398063861);
        cr->funcionesTime[2][9] = Cr_CrearFuncion_time(iEMG, -3539.7147712973637681, 3110.7433968026739421);
        cr->funcionesTime[3][9] = Cr_CrearFuncion_time(iEMG, -4217.6256802436282669, 3357.7982487642707383);
        cr->funcionesTime[4][9] = Cr_CrearFuncion_time(iEMG, -2244.0518432668391142, 2582.3296629548167402);
        cr->funcionesTime[5][9] = Cr_CrearFuncion_time(iEMG, -6005.6849099681594453, 5519.5407740847476816);
        cr->funcionesTime[6][9] = Cr_CrearFuncion_time(iEMG, -8096.0266785280673503, 5392.2298324425592000);
        cr->funcionesTime[7][9] = Cr_CrearFuncion_time(iEMG, -3284.3014592292879570, 3290.6943947021177337);
        cr->funcionesTime[0][10] = Cr_CrearFuncion_time(SSC, 10.0000000000000000, 99.0000000000000000);
        cr->funcionesTime[1][10] = Cr_CrearFuncion_time(SSC, 13.0000000000000000, 83.0000000000000000);
        cr->funcionesTime[2][10] = Cr_CrearFuncion_time(SSC, 9.0000000000000000, 99.0000000000000000);
        cr->funcionesTime[3][10] = Cr_CrearFuncion_time(SSC, 9.0000000000000000, 91.0000000000000000);
        cr->funcionesTime[4][10] = Cr_CrearFuncion_time(SSC, 14.0000000000000000, 91.0000000000000000);
        cr->funcionesTime[5][10] = Cr_CrearFuncion_time(SSC, 9.0000000000000000, 99.0000000000000000);
        cr->funcionesTime[6][10] = Cr_CrearFuncion_time(SSC, 10.0000000000000000, 99.0000000000000000);
        cr->funcionesTime[7][10] = Cr_CrearFuncion_time(SSC, 11.0000000000000000, 99.0000000000000000);
        cr->funcionesTime[0][11] = Cr_CrearFuncion_time(WAMP, 0.0000000000000000, 95.0000000000000000);
        cr->funcionesTime[1][11] = Cr_CrearFuncion_time(WAMP, 0.0000000000000000, 92.0000000000000000);
        cr->funcionesTime[2][11] = Cr_CrearFuncion_time(WAMP, 0.0000000000000000, 90.0000000000000000);
        cr->funcionesTime[3][11] = Cr_CrearFuncion_time(WAMP, 0.0000000000000000, 94.0000000000000000);
        cr->funcionesTime[4][11] = Cr_CrearFuncion_time(WAMP, 0.0000000000000000, 99.0000000000000000);
        cr->funcionesTime[5][11] = Cr_CrearFuncion_time(WAMP, 0.0000000000000000, 97.0000000000000000);
        cr->funcionesTime[6][11] = Cr_CrearFuncion_time(WAMP, 0.0000000000000000, 96.0000000000000000);
        cr->funcionesTime[7][11] = Cr_CrearFuncion_time(WAMP, 0.0000000000000000, 94.0000000000000000);

        // caracteristicas en el dominio de la frecuencia
        // PF
        cr->funcionesFreq[0][0] = Cr_CrearFuncion_freq(PF, 11.71875, 246.09375);
        cr->funcionesFreq[1][0] = Cr_CrearFuncion_freq(PF, 15.625, 246.09375);
        cr->funcionesFreq[2][0] = Cr_CrearFuncion_freq(PF, 11.71875, 246.09375);
        cr->funcionesFreq[3][0] = Cr_CrearFuncion_freq(PF, 11.71875, 246.09375);
        cr->funcionesFreq[4][0] = Cr_CrearFuncion_freq(PF, 15.625, 246.09375);
        cr->funcionesFreq[5][0] = Cr_CrearFuncion_freq(PF, 15.625, 246.09375);
        cr->funcionesFreq[6][0] = Cr_CrearFuncion_freq(PF, 3.90625, 246.09375);
        cr->funcionesFreq[7][0] = Cr_CrearFuncion_freq(PF, 11.71875, 246.09375);

        // PM
        cr->funcionesFreq[0][1] = Cr_CrearFuncion_freq(PM, 1.3512054435182814, 18305.34378653413);
        cr->funcionesFreq[1][1] = Cr_CrearFuncion_freq(PM, 59.46625104004316, 13312.296184491626);
        cr->funcionesFreq[2][1] = Cr_CrearFuncion_freq(PM, 0.0666713918680728, 18764.519901869688);
        cr->funcionesFreq[3][1] = Cr_CrearFuncion_freq(PM, 130.7657215288043, 23153.80187604565);
        cr->funcionesFreq[4][1] = Cr_CrearFuncion_freq(PM, 99.95446683609, 34798.13881650924);
        cr->funcionesFreq[5][1] = Cr_CrearFuncion_freq(PM, 1.2690244976398266, 28816.75462112257);
        cr->funcionesFreq[6][1] = Cr_CrearFuncion_freq(PM, 4.8153920456888, 38391.85545533415);
        cr->funcionesFreq[7][1] = Cr_CrearFuncion_freq(PM, 1.429190286505528, 19594.830428000307);

        // MNF
        cr->funcionesFreq[0][2] = Cr_CrearFuncion_freq(MNF, 44.56550210641688, 226.236070615309);
        cr->funcionesFreq[1][2] = Cr_CrearFuncion_freq(MNF, 58.76178047019322, 173.3548699353746);
        cr->funcionesFreq[2][2] = Cr_CrearFuncion_freq(MNF, 37.32122196678454, 232.16068609105236);
        cr->funcionesFreq[3][2] = Cr_CrearFuncion_freq(MNF, 42.02979184923082, 164.46662092720115);
        cr->funcionesFreq[4][2] = Cr_CrearFuncion_freq(MNF, 59.22539014946914, 173.8220895236365);
        cr->funcionesFreq[5][2] = Cr_CrearFuncion_freq(MNF, 43.41043219848682, 226.4034582221036);
        cr->funcionesFreq[6][2] = Cr_CrearFuncion_freq(MNF, 48.16643518279269, 226.2809431763998);
        cr->funcionesFreq[7][2] = Cr_CrearFuncion_freq(MNF, 46.617027512118106, 225.2900053911297);

        // MNM
        cr->funcionesFreq[0][3] = Cr_CrearFuncion_freq(MNM, 0.0495165109768681, 2857.940258283264);
        cr->funcionesFreq[1][3] = Cr_CrearFuncion_freq(MNM, 27.67137500596827, 1491.9820736095403);
        cr->funcionesFreq[2][3] = Cr_CrearFuncion_freq(MNM, 0.0032431472228279, 4076.518908280408);
        cr->funcionesFreq[3][3] = Cr_CrearFuncion_freq(MNM, 59.3097132463639, 5971.006828843492);
        cr->funcionesFreq[4][3] = Cr_CrearFuncion_freq(MNM, 7.347062028825186, 6372.754046157354);
        cr->funcionesFreq[5][3] = Cr_CrearFuncion_freq(MNM, 0.0473410412722787, 6245.846273076193);
        cr->funcionesFreq[6][3] = Cr_CrearFuncion_freq(MNM, 0.1800016157208831, 8324.934849046023);
        cr->funcionesFreq[7][3] = Cr_CrearFuncion_freq(MNM, 0.0523327944248211, 5900.56820455545);

        // MDF
        cr->funcionesFreq[0][4] = Cr_CrearFuncion_freq(MDF, 23.4375, 246.09375);
        cr->funcionesFreq[1][4] = Cr_CrearFuncion_freq(MDF, 31.25, 195.3125);
        cr->funcionesFreq[2][4] = Cr_CrearFuncion_freq(MDF, 19.53125, 246.09375);
        cr->funcionesFreq[3][4] = Cr_CrearFuncion_freq(MDF, 23.4375, 195.3125);
        cr->funcionesFreq[4][4] = Cr_CrearFuncion_freq(MDF, 27.34375, 195.3125);
        cr->funcionesFreq[5][4] = Cr_CrearFuncion_freq(MDF, 23.4375, 246.09375);
        cr->funcionesFreq[6][4] = Cr_CrearFuncion_freq(MDF, 23.4375, 246.09375);
        cr->funcionesFreq[7][4] = Cr_CrearFuncion_freq(MDF, 27.34375, 246.09375);

        // MDM
        cr->funcionesFreq[0][5] = Cr_CrearFuncion_freq(MDM, 0.010489351731154, 2713.186898629065);
        cr->funcionesFreq[1][5] = Cr_CrearFuncion_freq(MDM, 23.71695071030986, 1509.7513012075417);
        cr->funcionesFreq[2][5] = Cr_CrearFuncion_freq(MDM, 0.0007869823580993, 3587.42871963324);
        cr->funcionesFreq[3][5] = Cr_CrearFuncion_freq(MDM, 44.920385232728506, 5988.0419189624);
        cr->funcionesFreq[4][5] = Cr_CrearFuncion_freq(MDM, 2.81830878999725, 5828.958167650018);
        cr->funcionesFreq[5][5] = Cr_CrearFuncion_freq(MDM, 0.0097404529925521, 5801.73454024031);
        cr->funcionesFreq[6][5] = Cr_CrearFuncion_freq(MDM, 0.0369163676970497, 7939.055421370987);
        cr->funcionesFreq[7][5] = Cr_CrearFuncion_freq(MDM, 0.0107199965765622, 5657.707141409287);

    return SI;
}

void Cr_Procese(Cr_Control *cr) {
    int index = 0;
    for (int ch = 0; ch < NUM_CHANNELS; ch++) {
        //caracteristicas en el dominio del tiempo
        for (int f_idx = 0; f_idx < NUM_CAR_T; f_idx++) {
            Cr_FuncionCaracteristica_time fc = cr->funcionesTime[ch][f_idx];
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
     
      //Calcular FFT
        Cr_Caracteristicas vReal[SAMPLES]={0};
        Cr_Caracteristicas vImag[SAMPLES]={0};
        ArduinoFFT<Cr_Caracteristicas> FFT= ArduinoFFT<Cr_Caracteristicas>(vReal, vImag, SAMPLES,FS);

        for (uint16_t i = 0; i < WINDOW_SIZE; i++){
          vReal[i] = int16_t(cr->wnd[ch].canal[i]);
        }

        FFT.windowing(FFTWindow::Hamming, FFTDirection::Forward);
        FFT.compute(FFTDirection::Forward);
        FFT.complexToMagnitude(); 

         //caracteristicas en el dominio de la frecuencia
        for (int f_idx = 0; f_idx < NUM_CAR_F; f_idx++) {
            Cr_FuncionCaracteristica_freq fc = cr->funcionesFreq[ch][f_idx];
            Cr_Caracteristicas val = fc.func((const Cr_Caracteristicas*) vReal);
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

    IA_Predict(&c_modelo);
}


   
Cr_FuncionCaracteristica_time Cr_CrearFuncion_time(Cr_Caracteristicas (*f)(const Cr_Caracteristicas*, int), Cr_Caracteristicas min, Cr_Caracteristicas max) {
    Cr_FuncionCaracteristica_time fc;
    fc.func = f;
    fc.min = min;
    fc.max = max;
    return fc;
}

Cr_FuncionCaracteristica_freq Cr_CrearFuncion_freq(Cr_Caracteristicas (*f)(const Cr_Caracteristicas*), Cr_Caracteristicas min, Cr_Caracteristicas max) {
    Cr_FuncionCaracteristica_freq fc;
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

/*
//Cracteristicas en el dominio de la frecuencia
*/

//Función que calcula la frecuancia pico
Cr_Caracteristicas PF(const Cr_Caracteristicas* arr){
  Cr_Caracteristicas peakAmplitude = arr[0];
  Cr_Caracteristicas peakFrequency = 0;
    for (uint16_t i = 0; i < SAMPLES/2; i++) {
        Cr_Caracteristicas frequency = (i * FS) / SAMPLES;
        if (arr[i] > peakAmplitude) {
            peakAmplitude = arr[i];
            peakFrequency=frequency;
        }
    }
    return peakFrequency;
}

//Función que calcula la amplitud pico
Cr_Caracteristicas PM(const Cr_Caracteristicas* arr){
    Cr_Caracteristicas peakAmplitude = arr[0];
    for (uint16_t i = 0; i < SAMPLES/2; i++) {
        if (arr[i] > peakAmplitude) {
            peakAmplitude = arr[i];
        }
    }
    return peakAmplitude;
}

//Función que calcula la media de las magnitudes
Cr_Caracteristicas MNM(const Cr_Caracteristicas* arr){
    Cr_Caracteristicas sum = 0;
    int base= (SAMPLES/2)+1;
    for (uint16_t i = 0; i < base; i++) {
        sum += arr[i];
    }
    return sum / base;
}

//Función que calcula la media ponderada de las frecuencias según sus magnitudes.
Cr_Caracteristicas MNF(const Cr_Caracteristicas* arr){
    Cr_Caracteristicas weightedSum = 0;
    Cr_Caracteristicas totalMagnitude = 0;

    for (uint16_t i = 0; i < SAMPLES/2; i++) {
        Cr_Caracteristicas frequency = (i * FS) / SAMPLES;
        weightedSum += frequency * arr[i];
        totalMagnitude += arr[i];
    }

    if (totalMagnitude == 0) return 0; // Evitar división por cero
    return weightedSum / totalMagnitude;
}

//Determina la mediana de las magnitudes en el espectro de frecuencia
Cr_Caracteristicas MDM(const Cr_Caracteristicas* arr){
    int base= (SAMPLES/2)+1;
    // Copiar el array para no modificar el original
    Cr_Caracteristicas vCopy[base];
    for (uint16_t k = 0; k < base; k++) {
      vCopy[k]=arr[k];
    }

    // Ordenar el array
    for (uint16_t i = 0; i < base - 1; i++) {
        for (uint16_t j = i + 1; j < base; j++) {
            if (vCopy[i] > vCopy[j]) {
                Cr_Caracteristicas temp = vCopy[i];
                vCopy[i] = vCopy[j];
                vCopy[j] = temp;
            }
        }
    }

    // Calcular la mediana
    if (base % 2 == 0) {
        return (vCopy[base / 2 - 1] + vCopy[base / 4]) / 2.0;
    } else {
        return vCopy[base / 2];
    }
}


Cr_Caracteristicas MDF(const Cr_Caracteristicas* arr){
    Cr_Caracteristicas totalMagnitude = 0;
    for (uint16_t i = 0; i < SAMPLES/2; i++) {
        totalMagnitude += arr[i];
    }

    Cr_Caracteristicas cumulativeMagnitude = 0;
    for (uint16_t i = 0; i < SAMPLES/2; i++) {
        cumulativeMagnitude += arr[i];
        if (cumulativeMagnitude >= totalMagnitude / 2) {
            return (i * FS) / SAMPLES;
        }
    }
    return 0; // En caso de error
}



/* ===== RUTINAS DE INTERFAZ ====== */



/* == FIN DE RUTINAS DE INTERFAZ == */


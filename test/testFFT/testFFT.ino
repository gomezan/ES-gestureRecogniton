/*

	Example of use of the FFT library
  
  Copyright (C) 2014 Enrique Condes
  Copyright (C) 2020 Bim Overbohm (template, speed improvements)

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

/*
  In this example, the Arduino simulates the sampling of a sinusoidal 1000 Hz
  signal with an amplitude of 100, sampled at 5000 Hz. Samples are stored
  inside the vReal array. The samples are windowed according to Hamming
  function. The FFT is computed using the windowed samples. Then the magnitudes
  of each of the frequencies that compose the signal are calculated. Finally,
  the frequency with the highest peak is obtained, being that the main frequency
  present in the signal.
*/

#include "arduinoFFT.h"

/*
These values can be changed in order to evaluate the functions
*/
const uint16_t samples = 128; //This value MUST ALWAYS be a power of 2
const double signalFrequency = 499;
const double samplingFrequency = 500;
const uint8_t amplitude = 100;


float data[100]={ -36.68071161,  -33.59244251,   36.84223991,    5.35162523,   32.08713186,
  -23.09370854,   13.64324585,   91.39480708,   58.40297455,   10.62941011,
  -66.07582176,  -30.71827517,   31.11068175,  -21.5933858,   -17.83990975,
  -36.92452777,   47.84253634,  -51.85339764,  -33.48240905,  -13.21053586,
  -55.78957198,  -27.79930309,  -45.1713233,  -14.54495128,  147.41243756,
  102.19102962,  105.01017209,   75.98079447,  -71.59707438,  -27.47435042,
  -23.90732714,  -73.83648182, -147.03375837,  -86.29692864,  206.23841599,
  -12.57369371,  -82.18093746,   35.9218579,    94.94003063,  141.65248826,
 -132.67497155, -102.60326988,  -31.8800356,   -68.73325056,   56.63007293,
  -32.63152041,    6.35288224,  127.45148093,   52.70257666,  137.29382068,
  -33.56072832,  -80.45204224,    5.07908735,   54.65430565, -108.35726236,
  -22.36989656,  -38.9105823,   -53.82373398,  -21.28857845  -56.03922905,
   72.27256303, -145.05492783,  229.67380485,  108.40559963,  -31.99944526,
   -8.51380951,   19.3792609,  104.84117771,   18.79387612, -131.93797361,
 -106.53890144,  -36.33440269,  -90.7608899,   -77.98616235,  -41.06660438,
  149.04108796,   21.26397603,   12.62484717,  123.77963685,  277.29755483,
  -98.72794676,  -85.47552046, -166.49438843,  154.98578679,  -25.50976343,
  139.70479924, -175.95699013,  -67.27875113, -103.14829228,  385.56190589,
 -140.16326673,  -95.82222166,  -67.89333318, -230.55483147,  -57.55092159,
   25.36425391,   54.97859269,  -85.18765634,  132.99425166,  107.78337669};

/*
These are the input and output vectors
Input vectors receive computed results from FFT
*/
double vReal[samples]={0};
double vImag[samples]={0};

/* Create FFT object */
ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, samples, samplingFrequency);

#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02
#define SCL_PLOT 0x03

void setup()
{
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Ready");
}

void loop()
{
  /* Build raw data */
  double ratio = twoPi * signalFrequency / samplingFrequency; // Fraction of a complete cycle stored at each sample (in radians)
  for (uint16_t i = 0; i < 100; i++)
  {
    vReal[i] = int8_t(data[i]);/* Build data with positive and negative values*/
    //vReal[i] = uint8_t((amplitude * (sin(i * ratio) + 1.0)) / 2.0);/* Build data displaced on the Y axis to include only positive values*/
    vImag[i] = 0.0; //Imaginary part must be zeroed in case of looping to avoid wrong calculations and overflows
  }
  /* Print the results of the simulated sampling according to time */
  Serial.println("Data:");
  PrintVector(vReal, samples, SCL_TIME);
  FFT.windowing(FFTWindow::Hamming, FFTDirection::Forward);	/* Weigh data */
  Serial.println("Weighed data:");
  PrintVector(vReal, samples, SCL_TIME);
  FFT.compute(FFTDirection::Forward); /* Compute FFT */
  Serial.println("Computed Real values:");
  PrintVector(vReal, samples, SCL_INDEX);
  Serial.println("Computed Imaginary values:");
  PrintVector(vImag, samples, SCL_INDEX);
  FFT.complexToMagnitude(); /* Compute magnitudes */
  Serial.println("Computed magnitudes:");
  PrintVector(vReal, (samples >> 1), SCL_FREQUENCY);
  double x = FFT.majorPeak();
  Serial.println(x, 6);
  while(1); /* Run Once */
  // delay(2000); /* Repeat after delay */
}

void PrintVector(double *vData, uint16_t bufferSize, uint8_t scaleType)
{
  for (uint16_t i = 0; i < bufferSize; i++)
  {
    double abscissa;
    /* Print abscissa value */
    switch (scaleType)
    {
      case SCL_INDEX:
        abscissa = (i * 1.0);
	break;
      case SCL_TIME:
        abscissa = ((i * 1.0) / samplingFrequency);
	break;
      case SCL_FREQUENCY:
        abscissa = ((i * 1.0 * samplingFrequency) / samples);
	break;
    }
    Serial.print(abscissa, 6);
    if(scaleType==SCL_FREQUENCY)
      Serial.print("Hz");
    Serial.print(" ");
    Serial.println(vData[i], 4);
  }
  Serial.println();
}

#include "median.h"

#define BAUD_RATE 115200

Md_Control c_median;


void setup() {
  Serial.begin(BAUD_RATE);
}

void loop(){

  Md_Inicie(&c_median);
  Md_Procese(&c_median);
  IA_gesture test=7;
  Md_savePrediction(&c_median,test);
  Md_Procese(&c_median);
  test=18;
  Md_savePrediction(&c_median,test);
  Md_Procese(&c_median);
  test=4;
  Md_savePrediction(&c_median,test);
  Md_Procese(&c_median);

}
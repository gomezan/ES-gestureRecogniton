/* model.c    implementaci�n del módulo Display */


#include "model.h"
#include <Tiempo.h>
#include <display.h>
#include "Varios.h"

#include <GestureClassification_inferencing.h>

//modulos principales 
extern Tm_Control c_tiempo;
extern Dp_Control c_display;

// Definición de modelos Eloquent
int raw_feature_get_data(size_t offset, size_t length, float *out_ptr);
void print_inference_result(ei_impulse_result_t result);
uint16_t get_top_prediction(ei_impulse_result_t result);

/* Rutina para iniciar el módulo (su estructura de datos) */   
char IA_Inicie (IA_Control *ia, algoritmo   modelo, Cr_Caracteristicas *features)
   {

    ia->modelo = modelo;
    ia->features=features;
        
   return SI;
   };


                  
/* Rutina para procesar el módulo (dentro del loop de polling) */				
void IA_Procese (IA_Control *ia){

    int a=0;
   
   };



void print_inference_result(ei_impulse_result_t result) {

    // Print how long it took to perform inference
    ei_printf("Timing: DSP %d ms, inference %d ms, anomaly %d ms\r\n",
            result.timing.dsp,
            result.timing.classification,
            result.timing.anomaly);

    // Print the prediction results (object detection)
#if EI_CLASSIFIER_OBJECT_DETECTION == 1
    ei_printf("Object detection bounding boxes:\r\n");
    for (uint32_t i = 0; i < result.bounding_boxes_count; i++) {
        ei_impulse_result_bounding_box_t bb = result.bounding_boxes[i];
        if (bb.value == 0) {
            continue;
        }
        ei_printf("  %s (%f) [ x: %u, y: %u, width: %u, height: %u ]\r\n",
                bb.label,
                bb.value,
                bb.x,
                bb.y,
                bb.width,
                bb.height);
    }

    // Print the prediction results (classification)
#else
    ei_printf("Predictions:\r\n");
    for (uint16_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
        ei_printf("  %s: ", ei_classifier_inferencing_categories[i]);
        ei_printf("%.5f\r\n", result.classification[i].value);
    }
#endif

    // Print anomaly result (if it exists)
#if EI_CLASSIFIER_HAS_ANOMALY
    ei_printf("Anomaly prediction: %.3f\r\n", result.anomaly);
#endif

#if EI_CLASSIFIER_HAS_VISUAL_ANOMALY
    ei_printf("Visual anomalies:\r\n");
    for (uint32_t i = 0; i < result.visual_ad_count; i++) {
        ei_impulse_result_bounding_box_t bb = result.visual_ad_grid_cells[i];
        if (bb.value == 0) {
            continue;
        }
        ei_printf("  %s (%f) [ x: %u, y: %u, width: %u, height: %u ]\r\n",
                bb.label,
                bb.value,
                bb.x,
                bb.y,
                bb.width,
                bb.height);
    }
#endif

}

uint16_t get_top_prediction(ei_impulse_result_t result) {
    uint16_t top_index = 0;
    float max_value = result.classification[0].value;

    // Buscar el índice con la mayor probabilidad
    for (uint16_t i = 1; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
        if (result.classification[i].value > max_value) {
            max_value = result.classification[i].value;
            top_index = i;
        }
    }

    // Devolver la clase con mayor probabilidad
    return top_index;
}

/* ===== RUTINAS DE INTERFAZ ====== */
/* Rutina para activar un canal. Indica si se pudo activar. */
 char IA_Predict(IA_Control *ia){

  ei_impulse_result_t result = { 0 };

  // Definir la función de obtención de datos
    auto get_feature_data = [&ia](size_t offset, size_t length, float *out_ptr) -> int {
        memcpy(out_ptr, const_cast<float*>(ia->features + offset), length * sizeof(float));
        return 0;
    };

  signal_t features_signal;
  features_signal.total_length = NUM_CHANNELS*(NUM_CAR_T + NUM_CAR_F);  // Longitud total de características
  features_signal.get_data = get_feature_data; 

    EI_IMPULSE_ERROR res = run_classifier(&features_signal, &(result), false /* debug */);
    if (res != EI_IMPULSE_OK) {
        ei_printf("ERR: Failed to run classifier (%d)\n", res);
        return NO;
    }

   uint16_t pred=get_top_prediction(result);
   //print_inference_result( result);

    /*for(int j=0;j<NUM_CHANNELS*NUM_CAR;j++){
      Serial.print(ia->features[j]);
      Serial.print(",");
    }
    Serial.println();
    Serial.println(pred);
  */
  
  Dp_updatePrediction(&c_display,pred);
  return SI;  

 }
/* == FIN DE RUTINAS DE INTERFAZ == */

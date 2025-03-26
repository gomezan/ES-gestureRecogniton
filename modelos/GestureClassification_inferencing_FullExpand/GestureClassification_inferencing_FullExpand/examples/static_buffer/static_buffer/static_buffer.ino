/* Edge Impulse ingestion SDK
 * Copyright (c) 2022 EdgeImpulse Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/* Includes ---------------------------------------------------------------- */
#include <GestureClassification_inferencing.h>
#include "dataset.h"  // <--- INCLUIR TU DATASET

static uint16_t current_sample_index = 0;  // Para recorrer dataset dinámicamente

char max_index = 0;
float max_value = 0;

// Función para obtener los datos de la fila actual
int raw_feature_get_data(size_t offset, size_t length, float *out_ptr) {
    if (offset + length > FEATURE_COUNT) return -1;
    memcpy(out_ptr, &dataset[current_sample_index][offset], length * sizeof(float));
    return 0;
}

void print_inference_result(ei_impulse_result_t result);

void setup()
{
    Serial.begin(115200);
    while (!Serial);
    Serial.println("Edge Impulse Inferencing Demo with Dataset");
}

void loop()
{
    ei_printf("\n[Sample %d] Running inference...\n", current_sample_index);

    if (FEATURE_COUNT != EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE) {
        ei_printf("ERROR: EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE (%lu) != dataset features (%d)\n",
                  EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, FEATURE_COUNT);
        delay(1000);
        return;
    }

    ei_impulse_result_t result = { 0 };

    signal_t features_signal;
    features_signal.total_length = FEATURE_COUNT;
    features_signal.get_data = &raw_feature_get_data;

    EI_IMPULSE_ERROR res = run_classifier(&features_signal, &result, false);
    if (res != EI_IMPULSE_OK) {
        ei_printf("ERR: Failed to run classifier (%d)\n", res);
        return;
    }

    max_value=result.classification[0].value;
    max_index=0;
    for (uint16_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {

        if(result.classification[i].value>max_value){
          max_value=result.classification[i].value;
          max_index=atoi(ei_classifier_inferencing_categories[i]);
        }
    }

    Serial.println(max_index);

    // Avanzamos al siguiente sample
    current_sample_index++;
    if (current_sample_index >= NUM_SAMPLES) {
        ei_printf("All samples processed.\n");
        while (1); // Detener loop
    }

    delay(500); // Pausa entre muestras
}

void print_inference_result(ei_impulse_result_t result) {
    ei_printf("Timing: DSP %d ms, inference %d ms, anomaly %d ms\n",
              result.timing.dsp,
              result.timing.classification,
              result.timing.anomaly);

#if EI_CLASSIFIER_OBJECT_DETECTION == 1
    for (uint32_t i = 0; i < result.bounding_boxes_count; i++) {
        ei_impulse_result_bounding_box_t bb = result.bounding_boxes[i];
        if (bb.value == 0) continue;
        ei_printf("  %s (%f) [ x: %u, y: %u, w: %u, h: %u ]\n",
                  bb.label, bb.value, bb.x, bb.y, bb.width, bb.height);
    }
#else
    ei_printf("Predictions:\n");
    for (uint16_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
        ei_printf("  %s: %.5f\n", ei_classifier_inferencing_categories[i],
                  result.classification[i].value);
    }
#endif

#if EI_CLASSIFIER_HAS_ANOMALY
    ei_printf("Anomaly prediction: %.3f\n", result.anomaly);
#endif
}

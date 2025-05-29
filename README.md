# Reconocimiento de Gestos a través de Aprendizaje Automático en un Sistema Embebido

Este proyecto implementa un sistema de reconocimiento de gestos de mano en tiempo real con fines de rehabilitación de la función motora. Utiliza señales electromiográficas de superficie (sEMG) obtenidas del antebrazo, aplicando modelos de aprendizaje automático para detectar y clasificar gestos.

El sistema está diseñado para ejecutarse de forma embebida en el microcontrolador **XIAO ESP32S3 de Seeed Studio**, permitiendo una implementación ligera y eficiente.

## Características

- **Reconocimiento de gestos en tiempo real** mediante señales sEMG.
- **Modelos de clasificación** entrenados: Bagged Forest (BF) y Redes Neuronales (NN).
- **Procesamiento embebido eficiente** desplegado en ESP32S3.
- **Aplicación práctica** orientada a la rehabilitación de la función motora de la mano.

## Estructura del Proyecto

ES-gestureRecognition/
├── Main/                         # Versión más estable del sistema (uso de NN en tiempo real)
│   ├── main.ino
│   └── src/                      # Archivos fuente y procesamiento embebido
│
├── versions/                     # Versiones previas del sistema
│   ├── version_JT/              # Esta versión del sistema solo usa 12 características en el dominio del tiempo.
│   └── Inicial/                 # Esta versión del sistema no soporta el tratamiento de ventanas solapantes y tampoco el post-procesamiento usando un filtro de medianas.
│
├── test/                         # Pruebas unitarias y bloques de prueba del sistema
│   ├── feature_extraction/
│   ├── model_inference/
│   ├── signal_acquisition/
│   └── Post-processing/
|   └── Windows_segmentatio/
│
├── modelos/                      # Modelos entrenados y evaluaciones
│   ├── NN/                      # Versiones de modelos de redes neuronales (.keras.h5, Edge Impulse)
│   └── BF/                      # Modelos Bagged Forest (.joblib, .h)
│
├── README.md
└── LICENSE


│
├── modelos/ # Modelos entrenados y evaluaciones
│ ├── NN/ # Versiones de modelos de redes neuronales (.keras.h5, Edge Impulse)
│ └── BF/ # Modelos Bagged Forest (.joblib, .h)
│
├── README.md
└── LICENSE

## Requisitos

- Microcontrolador **Seeed Studio XIAO ESP32S3**
- Sensor sEMG BioAmp EXG

## Cómo Ejecutar el Proyecto

### 1. Recolección de Datos sEMG

Utiliza el código embebido para capturar señales desde sensores sEMG conectados al microcontrolador. A continuación se filtran, almacenan y se extraen sus caractersticas para la inferencia del modelo. 

### 2. Preprocesamiento y Extracción de Características

Se realiza el filtrado y la extracción de 18 características (como RMS, MAV, ZC, etc.) para alimentar al modelo de clasificación.

### 3. Entrenamiento del Modelo

Entrena modelos con los scripts correspondientes y exporta versiones compatibles con el entorno embebido.

### 4. Implementación en el ESP32S3

Carga el firmware de la carpeta `Main/` usando PlatformIO o Arduino IDE. Esta versión contiene la arquitectura más estable basada en redes neuronales.

### 5. Pruebas

La carpeta `test/` contiene módulos independientes que prueban funcionalidades clave del sistema: adquisición de señales, extracción de características e inferencia.

## Gestos Reconocidos

Algunos ejemplos de gestos detectables incluyen:

- ✊ Puño cerrado
- ✋ Mano descanso
- 👉 Pinza pulgar-indice
- 👉 Pinza pulgar-medio
- 👉 Pinza pulgar-anular
- 👉 Pinza pulgar-menique

## Licencia

Este proyecto está licenciado bajo la Licencia Apache 2.0. Consulta el archivo [LICENSE](LICENSE)

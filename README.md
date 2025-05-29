# Reconocimiento de Gestos a través de Aprendizaje Automático en un Sistema Embebido

Este proyecto implementa un sistema de reconocimiento de gestos de mano en tiempo real con fines de rehabilitación de la función motora. Utiliza señales electromiográficas de superficie (sEMG) obtenidas del antebrazo, aplicando modelos de aprendizaje automático para detectar y clasificar gestos.

El sistema está diseñado para ejecutarse de forma embebida en el microcontrolador **XIAO ESP32S3 de Seeed Studio**, permitiendo una implementación ligera y eficiente.

## Características

- **Reconocimiento de gestos en tiempo real** mediante señales sEMG.
- **Modelos de clasificación** entrenados: Bagged Forest (BF) y Redes Neuronales (NN).
- **Procesamiento embebido eficiente** desplegado en ESP32S3.
- **Aplicación práctica** orientada a la rehabilitación de la función motora de la mano.


## 📁 Estructura del Proyecto

- **[`Main/`](./Main)**  
  Versión más estable del sistema. Utiliza una red neuronal (NN) para el reconocimiento en tiempo real. Contiene:
  - `main.ino`: programa principal.
  - [`src/`](./Main/src): código fuente y procesamiento embebido.

- **[`versions/`](./versions)**  
  Versiones previas del sistema.
  - `version_JT/`: usa 12 características en el dominio del tiempo.
  - `Inicial/`: versión básica sin ventanas solapadas ni post-procesamiento.

- **[`test/`](./test)**  
  Pruebas unitarias y bloques individuales del sistema.
  - `feature_extraction/`, `model_inference/`, `signal_acquisition/`, `Post-processing/`.

- **[`modelos/`](./modelos)**  
  Modelos entrenados y listos para uso.
  - `NN/`: modelos de redes neuronales (.h5, Edge Impulse).
  - `BF/`: modelos Bagged Forest (.joblib, .h).

- `README.md` y `LICENSE`: documentación y licencia del proyecto.



## Requisitos

- Microcontrolador **Seeed Studio XIAO ESP32S3**
- Sensor sEMG BioAmp EXG

## Cómo Ejecutar el Proyecto

### 1. Despliegue del Modelo

Tomar cualquier modelo en la carpeta modelos o cualquier modelo compatible con el entorno embebido y e incluirlo en el proyecto .

### 1. Implementación en el ESP32S3

Carga el firmware de la carpeta `Main/` usando PlatformIO o Arduino IDE. Esta versión contiene la arquitectura más estable basada en redes neuronales.



## Funcionamiento

### 1. Recolección de Datos sEMG

Utiliza el código embebido para capturar señales desde sensores sEMG conectados al microcontrolador. A continuación se filtran, almacenan y se extraen sus caractersticas para la inferencia del modelo. 

### 2. Preprocesamiento y Extracción de Características

Se realiza el filtrado de las señales, se segmentan en ventanas de 200 ms y posteriormente se extraen 18 características (como RMS, MAV, ZC, etc.) para alimentar al modelo de clasificación.

### 3. Inferencia del Modelo

El modelo realiza la inferencia sobre el vector de caracteristicas calculado.

### 4. Post-procesamiento

El sistema busca generar una sola respuesta coherente a la salida empleando bloques asociados a esto, como un filtro de medianas y un bloque de envio serial.


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

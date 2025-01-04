#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#ifdef ESP32
#define ADC_MAX 4095.0
#else
#define ADC_MAX 1023.0
#endif


//Pines


// Pines de los sensores
#define DHTPIN 4
#define DHTTYPE DHT11
#define TEMPPIN 34
#define LUZPIN 35

// Pines para el control del TRIAC
const int acoplador = 36;  
const int disparoTRIAC = 16;

// Pines para el control del motor
const int IN1 = 12;                 // Pin de salida digital A
const int IN2 = 13;                 // Pin de salida digital B


// Variables globales


// Variables del control del TRIAC
const int umbralCero = 10;           // Umbral para detección de cruce por cero
const int tiempoEntreCeros = 20;     // Tiempo conocido entre cruces por cero (ms)
int retrasoPulso = 5;                // Retraso desde el cruce por cero hasta el pulso (ms)
bool cruzoPorCero = false;           // Flag para detectar cruce por cero
unsigned long tiempoUltimoCero = 0;  // Tiempo del último cruce por cero

// Variables del control del motor
const int limiteInferior = 10;       // Límite inferior del rango medio
const int limiteSuperior = 20;       // Límite superior del rango medio

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Inicialización del puerto serie
  Serial.begin(115200);

  // Inicialización de los sensores
  dht.begin();
  pinMode(TEMPPIN, INPUT);
  pinMode(LUZPIN, INPUT);

  // Inicialización del control del TRIAC
  pinMode(acoplador, INPUT);
  pinMode(disparoTRIAC, OUTPUT);

  // Inicialización del control del motor
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}

float leerHumedad() {
  float humedad = dht.readHumidity();
  if (isnan(humedad)) {
    return -1;
  }
  return humedad;
}

float leerTemperatura() {
  int valorTemp = analogRead(TEMPPIN);
  float voltajeTemp = valorTemp * (3.3 / ADC_MAX);
  return voltajeTemp * 20;  // Map 0-3.3V to 0-66°C
}

int leerLuminosidad() {
  int valorLuz = analogRead(LUZPIN);
  float voltajeLuz = valorLuz * (3.3 / 1023.0);
  return voltajeLuz * 30.303;  // Map 0-3.3V to 0-100%
}

void enviarDatos(float temperatura, float humedad, int luminosidad) {
  if (humedad == -1) {
    Serial.println("-1"); //Error en las lecturas
  } else {
    Serial.print((int)temperatura);
    Serial.print(",");
    Serial.print((int)humedad);
    Serial.print(",");
    Serial.println(luminosidad);
  }
}


void detectarCrucePorCero(int valorAnalogico) {
  if (!cruzoPorCero && valorAnalogico <= umbralCero) {
    cruzoPorCero = true;
    tiempoUltimoCero = millis();
  }
}

void dispararPulso() {
  if (cruzoPorCero && (millis() - tiempoUltimoCero >= retrasoPulso)) {
    digitalWrite(disparoTRIAC, HIGH);  // Enviar pulso
    delay(1);                              // Duración del pulso (1 ms)
    digitalWrite(disparoTRIAC, LOW);   // Apagar pulso
    cruzoPorCero = false;                  // Resetear flag de cruce por cero
  }
}

void resetearFlag() {
  if (millis() - tiempoUltimoCero >= tiempoEntreCeros) {
    cruzoPorCero = false;
  }
}

void controlMotor(int parametro) {
  if (parametro < limiteInferior) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } 
  else if (parametro >= limiteInferior && parametro <= limiteSuperior) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  } 
  else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
}

void loop() {
  float humedad = leerHumedad();
  float temperatura = leerTemperatura();
  int luminosidad = leerLuminosidad();
  enviarDatos(temperatura, humedad, luminosidad);
  
  int valorAcoplador = analogRead(acoplador);
  detectarCrucePorCero(valorAcoplador);
  dispararPulso();
  resetearFlag();

  controlMotor(temperatura);

  delay(500);
}
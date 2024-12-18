#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Configuración de pines
#define DHTPIN 4       // Pin digital para el DHT11 (humedad)
#define DHTTYPE DHT11
#define TEMPPIN 34     // Pin analógico para temperatura en ESP32
#define LUZPIN 35      // Pin analógico para luminosidad en ESP32

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(TEMPPIN, INPUT);
  pinMode(LUZPIN, INPUT);
}

void loop() {
  // Leer humedad del DHT11
  float humedad = dht.readHumidity();
  if (isnan(humedad)) {
    Serial.println("Error al leer la humedad");
    humedad = -1;
  }

  // Leer temperatura desde entrada analógica
  int valorTemp = analogRead(TEMPPIN);
  float voltajeTemp = valorTemp * (3.3 / 4095.0); // Ajuste para ESP32 (12 bits ADC)
  float temperatura = (voltajeTemp - 0.5) * 100;  // Ajustar según el sensor utilizado

  // Leer luminosidad desde entrada analógica
  int valorLuz = analogRead(LUZPIN);
  float voltajeLuz = valorLuz * (3.3 / 4095.0); // Ajuste para ESP32 (12 bits ADC)
  int luminosidad = map(voltajeLuz * 100, 0, 330, 0, 100);  // Convertir a porcentaje

  // Verificar si hay errores antes de enviar
  if (humedad == -1) {
    Serial.println("Error en las lecturas. No se enviarán datos.");
  } else {
    // Enviar datos en el formato: "temperatura,humedad,luminosidad"
    Serial.print((int)temperatura);
    Serial.print(",");
    Serial.print((int)humedad);
    Serial.print(",");
    Serial.println(luminosidad);
  }

  delay(2000);  // Esperar antes de la siguiente lectura
}
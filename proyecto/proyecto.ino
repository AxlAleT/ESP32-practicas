#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 4
#define DHTTYPE DHT11
#define TEMPPIN 34
#define LUZPIN 35

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(TEMPPIN, INPUT);
  pinMode(LUZPIN, INPUT);
}

void loop() {
  float humedad = dht.readHumidity();
  if (isnan(humedad)) {
    Serial.println("Error al leer la humedad");
    humedad = -1;
  }

  int valorTemp = analogRead(TEMPPIN);
  float voltajeTemp = valorTemp * (3.3 / 1023.0);
  float temperatura = voltajeTemp * 20;  // Map 0-3.3V to 0-66°C

  int valorLuz = analogRead(LUZPIN);
  float voltajeLuz = valorLuz * (3.3 / 1023.0);
  int luminosidad = voltajeLuz * 30.303;  // Map 0-3.3V to 0-100%

  if (humedad == -1) {
    Serial.println("Error en las lecturas. No se enviarán datos.");
  } else {
    Serial.print((int)temperatura);
    Serial.print(",");
    Serial.print((int)humedad);
    Serial.print(",");
    Serial.println(luminosidad);
  }

  delay(2000);
}
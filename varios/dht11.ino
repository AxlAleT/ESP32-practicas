#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Configuración del pin y tipo de sensor
#define DHTPIN 4     // Pin del sensor DHT11
#define DHTTYPE DHT11
#define LUZPIN A0    // Pin analógico simulado para el sensor de luz

// Inicialización del sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

// Función para inicializar el DHT11
void inicializarDHT() {
  Serial.println("Inicializando el sensor DHT11...");
  dht.begin();
}

// Función para leer la humedad
float leerHumedad() {
  float humedad = dht.readHumidity();
  if (isnan(humedad)) {
    Serial.println("Error al leer la humedad");
    return -1; // Valor de error
  }
  return humedad;
}

// Función para leer la temperatura
float leerTemperatura() {
  float temperatura = dht.readTemperature();
  if (isnan(temperatura)) {
    Serial.println("Error al leer la temperatura");
    return -1; // Valor de error
  }
  return temperatura;
}

// Función para leer la "luz" (valor simulado usando un pin analógico)
int leerLuz() {
  int luz = analogRead(LUZPIN); // Lectura del pin analógico
  luz = map(luz, 0, 1023, 0, 100); // Convertir de 0-1023 a 0-100
  return luz;
}

void setup() {
  Serial.begin(115200); // Configuración del baud rate
  inicializarDHT();
  pinMode(LUZPIN, INPUT); // Configuración del pin de luz
}

void loop() {
  // Leer los valores de los sensores
  float humedad = leerHumedad();
  float temperatura = leerTemperatura();
  int luz = leerLuz();

  // Verificar si hay errores antes de enviar
  if (humedad == -1 || temperatura == -1) {
    Serial.println("Error en las lecturas. No se enviarán datos.");
  } else {
    // Enviar datos en el formato requerido: "temperatura,humedad,luz"
    Serial.print((int)temperatura); // Convertir temperatura a entero
    Serial.print(",");
    Serial.print((int)humedad); // Convertir humedad a entero
    Serial.print(",");
    Serial.println(luz); // Luz simulada
  }

  delay(2000); // Espera 2 segundos antes de la próxima lectura
}

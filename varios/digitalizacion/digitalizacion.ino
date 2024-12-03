const int signalPin1 = 34; // GPIO para señal 1
const int signalPin2 = 35; // GPIO para señal 2
const int signalPin3 = 32; // GPIO para señal 3

// Factor de conversión de lectura ADC a voltios
const float adcToVolts = 3.3 / 4095.0; // 3.3V es el voltaje de referencia del ADC

void setup() {
  Serial.begin(115200); // Inicializa la comunicación serie
  while (!Serial);      // Espera a que el puerto serie esté listo
  Serial.println("Leyendo señales...");
}

void loop() {
  // Leer valores analógicos
  int signal1 = analogRead(signalPin1);
  int signal2 = analogRead(signalPin2);
  int signal3 = analogRead(signalPin3);

  // Convertir valores a voltios
  float voltage1 = signal1 * adcToVolts;
  float voltage2 = signal2 * adcToVolts;
  float voltage3 = signal3 * adcToVolts;

  // Enviar valores en voltios por el puerto serie
  Serial.print("Signal 1: ");
  Serial.print(voltage1, 2); // Mostrar con 2 decimales
  Serial.print(" V | Signal 2: ");
  Serial.print(voltage2, 2);
  Serial.print(" V | Signal 3: ");
  Serial.print(voltage3, 2);
  Serial.println(" V");

  delay(500); // Espera 500 ms entre lecturas
}


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
  int signal3 = analogReadMilliVolts(signalPin3);


  float voltage3 = signal3 * adcToVolts;

  Serial.print(" V | Signal 3: ");
  Serial.print(voltage3, 2);
  Serial.println(" V");

  delay(500); // Espera 500 ms entre lecturas
}

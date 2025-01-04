// Variables globales
const int acoplador = 36;  // Pin de entrada analógica
const int disparoTRIAC = 16;     // Pin de salida digital

const int umbralCero = 10;           // Umbral para detección de cruce por cero
const int tiempoEntreCeros = 20;     // Tiempo conocido entre cruces por cero (ms)
int retrasoPulso = 5;                // Retraso desde el cruce por cero hasta el pulso (ms)

bool cruzoPorCero = false;           // Flag para detectar cruce por cero
unsigned long tiempoUltimoCero = 0;  // Tiempo del último cruce por cero

void setup() {
  pinMode(acoplador, INPUT);
  pinMode(disparoTRIAC, OUTPUT);
  Serial.begin(115200);
}

void detectarCrucePorCero(int valorAnalogico) {
  if (valorAnalogico <= umbralCero && !cruzoPorCero) {
    cruzoPorCero = true;
    tiempoUltimoCero = millis();
    Serial.println("Cruce por cero detectado");
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

void loop() {
  int valorAnalogico = analogRead(acoplador);
  detectarCrucePorCero(valorAnalogico);
  dispararPulso();
  resetearFlag();
}

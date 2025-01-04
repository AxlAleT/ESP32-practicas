// Variables globales
const int IN1 = 12;                 // Pin de salida digital A
const int IN2 = 13;                 // Pin de salida digital B
const int limiteInferior = 10;       // Límite inferior del rango medio
const int limiteSuperior = 20;       // Límite superior del rango medio

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  ejecutarControlMotor();
  delay(500);  // Retardo para facilitar la observación en el monitor serie
}

void ejecutarControlMotor() {
  int parametro = leerParametro();  // Simulación de la obtención del parámetro
  controlMotor(parametro);
}

// Función para controlar el motor según el parámetro recibido
void controlMotor(int parametro) {
  if (parametro < limiteInferior) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    Serial.println("Motor girando en sentido 1");
  } 
  else if (parametro >= limiteInferior && parametro <= limiteSuperior) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    Serial.println("Motor apagado");
  } 
  else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    Serial.println("Motor girando en sentido 2");
  }
}

// Función simulada para obtener el parámetro (puedes modificarla según tu sistema)
int leerParametro() {
  static int valor = 5;
  valor += 5;  // Simular cambio del parámetro
  if (valor > 25) valor = 0;
  return valor;
}

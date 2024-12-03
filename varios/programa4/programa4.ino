#define LED_1 2
#define LED_2 0
#define LED_3 4
#define LED_4 16
#define LED_5 17
#define LED_6 5
#define LED_7 18

void setup() {
    pinMode(LED_1, OUTPUT);
    pinMode(LED_2, OUTPUT);
    pinMode(LED_3, OUTPUT);
    pinMode(LED_4, OUTPUT);
    pinMode(LED_5, OUTPUT);
    pinMode(LED_6, OUTPUT);
    pinMode(LED_7, OUTPUT);
}

void cortina() {
    // Encendido de LED 4 hacia los extremos
    digitalWrite(LED_4, HIGH);
    delay(100);

    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_5, HIGH);
    delay(100);

    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_6, HIGH);
    delay(100);

    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_7, HIGH);
    delay(100);

    // Apagado en sentido contrario
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_7, LOW);
    delay(100);

    digitalWrite(LED_2, LOW);
    digitalWrite(LED_6, LOW);
    delay(100);

    digitalWrite(LED_3, LOW);
    digitalWrite(LED_5, LOW);
    delay(100);

    digitalWrite(LED_4, LOW);
    delay(100);
}

void loop() {
    cortina();  // Ejecuta la animación de cortina en bucle
}

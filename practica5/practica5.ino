int leds[] = {2, 0, 4, 16, 17, 5, 18};
int numLeds = sizeof(leds) / sizeof(leds[0]);
int delayTime = 100;
int dipSwitchPins[] = {12, 14, 27, 26, 33, 32, 35};
int pot1 = 13;
int pot2 = 15;
int dato = 25;
float lcb = 0.09;

void setup() {
  for (int i = 0; i < numLeds; i++) {
    pinMode(leds[i], OUTPUT);
  }
  for (int i = 0; i < 6; i++) {
    pinMode(dipSwitchPins[i], INPUT_PULLUP);
  }
  pinMode(dipSwitchPins[6], INPUT);
  pinMode(pot1, INPUT);
  pinMode(pot2, INPUT);
  pinMode(dato, INPUT);
  Serial.begin(9600);
  analogReadResolution(10);
}

void loop() {
  int activeSwitch = -1;
  
  for (int i = 0; i < 7; i++) {
    if (!digitalRead(dipSwitchPins[i])) {
      activeSwitch = i;
      for (int i = 0; i < numLeds; i++) {
        digitalWrite(leds[i], LOW);
      }
      break;
    }
  }
  
  switch (activeSwitch) {
    case -1:  // Ningún interruptor activo
      for (int i = 0; i < numLeds; i++) {
        digitalWrite(leds[i], HIGH);
      }
      break;
    case 0:
      ledCorrimientoIdaVuelta();
      break;
    case 1:
      ledCorrimientoCentro();
      break;
    case 2:
      ledCorrimientoCircular();
      break;
    case 3:
      readVoltage(pot1, "Potenciómetro 1");
      break;
    case 4:
      readVoltage(pot2, "Potenciómetro 2");
      break;
    case 5:
      readVoltage(dato, "Sensor de temperatura");
      break;
    case 6:
      promedioVoltajes();
      break;
  }
}

void ledCorrimientoIdaVuelta() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(leds[i], HIGH);
    delay(delayTime);
    digitalWrite(leds[i], LOW);
  }
  for (int i = numLeds - 2; i >= 0; i--) {
    digitalWrite(leds[i], HIGH);
    delay(delayTime);
    digitalWrite(leds[i], LOW);
  }
}

void ledCorrimientoCentro() {
  int middle = numLeds / 2;
  digitalWrite(leds[middle], HIGH);
  delay(delayTime);
  digitalWrite(leds[middle], LOW);
  for (int offset = 1; offset <= middle; offset++) {
    digitalWrite(leds[middle - offset], HIGH);
    digitalWrite(leds[middle + offset], HIGH);
    delay(delayTime);
    digitalWrite(leds[middle - offset], LOW);
    digitalWrite(leds[middle + offset], LOW);
  }
}

void readVoltage(int pin, const char* name) {
  int value = analogRead(pin);
  float voltage = value * (3.3 / 1023.0);
  Serial.print(name);
  Serial.print(" -> Voltaje leído: ");
  Serial.println(voltage, 2);
  delay(1000);
}

void promedioVoltajes() {
  int value1 = analogRead(pot1);
  int value2 = analogRead(pot2);
  int value3 = analogRead(dato);
  float promedio = ((value1 + value2 + value3) * (3.3 / 1023.0)) / 3.0;
  Serial.print("Promedio de voltajes: ");
  Serial.println(promedio, 2);
  delay(1000);
}

void toggle(int LED_A, int LED_B) {
    digitalWrite(LED_A, 0);
    digitalWrite(LED_B, 1);
}

void ledCorrimientoCircular() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(leds[i], HIGH);
    delay(delayTime);
    digitalWrite(leds[i], LOW);
  }
}
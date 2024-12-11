#define adc0 13
#define adc1 15
#define adc2 25
int valoradc0,valoradc1,valoradc2;
char dato=0;

void readVoltage(int pin, const char* name) {
  int value = analogRead(pin);
  float voltage = value * (3.3 / 1023.0);
  Serial.print(name);
  Serial.print(" -> Voltaje leído: ");
  Serial.println(voltage, 2);
  delay(1000);
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  if(dato=='1'){
    readVoltage(adc0, "Sensor 1");
  }
  if(dato=='2'){
    readVoltage(adc1, "Sensor 2");
  }
}

void serialEvent(){
  while(Serial.available()){
    dato=Serial.read();
    Serial.println(dato);
    switch(dato){
      case '1':
        readVoltage(adc0, "Sensor 1");
      break;
      case '2':
        readVoltage(adc1, "Sensor 2");
      break;
    }
  }
}
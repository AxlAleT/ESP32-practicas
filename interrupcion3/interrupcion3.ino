char dato;

void serialEvent(){
  while(Serial.available()){
    dato = Serial.read();
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(dato);
  if(dato=='1'){
    Serial.println("Número 1");
  } else if(dato=='2'){
    Serial.println("Número 2");
  } else if(dato=='3'){
    Serial.println("Número 3");
  } else{
    dato = '0';
  }
  delay(500);
}

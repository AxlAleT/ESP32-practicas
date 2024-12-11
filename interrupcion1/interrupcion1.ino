#define boton 12
#define led 2
bool estado = false;

void IRAM_ATTR Encender(){
  estado = !estado;
  digitalWrite(led,estado);
  Serial.println("interrupción");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200 );
  pinMode(led, OUTPUT);
  pinMode(boton, INPUT_PULLUP);
  attachInterrupt(boton,Encender,RISING);
}

/*void serialEvent(){
  while(Serial.available()){
    dato=Serial.read();
  }
}*/

void loop() {
  // put your main code here, to run repeatedly:

}

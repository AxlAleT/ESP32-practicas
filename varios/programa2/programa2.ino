#define LED_1 2 
#define LED_2 0
#define LED_3 4
#define LED_4 16
#define LED_5 17
#define LED_6 5
#define LED_7 18
#define LED_8 19


void setup() {
    pinMode(LED_1, OUTPUT);
    pinMode(LED_2, OUTPUT);
    pinMode(LED_3, OUTPUT);
    pinMode(LED_4, OUTPUT); 
    pinMode(LED_5, OUTPUT);
    pinMode(LED_6, OUTPUT);
    pinMode(LED_7, OUTPUT);
    pinMode(LED_8, OUTPUT);
}

void toggle(LED_A, LED_B){
    digitalWrite(LED_A,0);
    digitalWrite(LED_B,1);
}

void loop() {
    digitalWrite(LED_1, 1);
    delay(1000);  // Espera 1 segundo
    toggle(LED_1, LED_2);
    delay(1000);  // Espera 1 segundo
    toggle(LED_2, LED_3);
    delay(1000);  // Espera 1 segundo
    toggle(LED_3, LED_4);
    delay(1000);  // Espera 1 segundo
    toggle(LED_4,LED_5);
    delay(1000);  // Espera 1 segundo
    toggle(LED_5, LED_6);
    delay(1000);  // Espera 1 segundo

}

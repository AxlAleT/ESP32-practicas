#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SENSOR_PIN A0
#define HUMIDITY_PIN A1
#define FAN_PIN 9
#define LED_PIN 13

// Inicializar la pantalla LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

struct SensorData {
    float temperature;
    float humidity;
};

// Clase para manejar el control del invernadero
class GreenhouseControl {
  private:
    int fanPin;
    int ledPin;
    float tempThreshold;
    float humThreshold;

  public:
    GreenhouseControl(int fan, int led, float tempThres, float humThres) {
        fanPin = fan;
        ledPin = led;
        tempThreshold = tempThres;
        humThreshold = humThres;
        pinMode(fanPin, OUTPUT);
        pinMode(ledPin, OUTPUT);
    }

    void update(SensorData *data) {
        if (data->temperature > tempThreshold) {
            digitalWrite(fanPin, HIGH);
        } else {
            digitalWrite(fanPin, LOW);
        }

        if (data->humidity < humThreshold) {
            digitalWrite(ledPin, HIGH);
        } else {
            digitalWrite(ledPin, LOW);
        }
    }
};

// Declaración de funciones
float readTemperature(int pin);
float readHumidity(int pin);
void displayData(SensorData *data);

GreenhouseControl greenhouse(FAN_PIN, LED_PIN, 25.0, 40.0);

void setup() {
    Serial.begin(9600);
    lcd.begin();
    lcd.backlight();
}

void loop() {
    // Leer los sensores y almacenar los valores en una estructura
    SensorData data;
    data.temperature = readTemperature(SENSOR_PIN);
    data.humidity = readHumidity(HUMIDITY_PIN);

    // Actualizar el estado del invernadero
    greenhouse.update(&data);

    // Mostrar los datos en el LCD
    displayData(&data);

    delay(1000);
}

float readTemperature(int pin) {
    int reading = analogRead(pin);
    float voltage = reading * (5.0 / 1023.0);
    float temperature = (voltage - 0.5) * 100;
    return temperature;
}

float readHumidity(int pin) {
    int reading = analogRead(pin);
    return map(reading, 0, 1023, 0, 100);
}

void displayData(SensorData *data) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(data->temperature);
    lcd.print(" C");

    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(data->humidity);
    lcd.print(" %");
}

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
int fan = 9;
int motionSensor = 11;
int pump = 10;
int buzzer=12;
#define DHTPIN 2     
#define DHTTYPE    DHT11     
int sensorPin=A1;
int lightPin=4;
#include <Wire.h> // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>
int sensorValue =0;
int moistureValue =0;
int motionValue =0;
LiquidCrystal_I2C lcd(0x27,20,4);

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

void setup() {
   pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(4, OUTPUT);
  pinMode(10, OUTPUT);
  
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  Serial.begin (9600);
  lcd.begin(16, 2);
  pinMode(fan,OUTPUT);
  dht.begin();
  
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  
}

void loop() {
  sensorValue = analogRead(A1);
  moistureValue = analogRead(A0);
  motionValue = digitalRead(11);
  Serial.println(sensorValue);
Serial.println(moistureValue);

 if(sensorValue >= 29.30) {
  
  digitalWrite(lightPin, HIGH);
  delay (2000);
  }else  {
   
      digitalWrite(lightPin, LOW);
      
      delay (2000);   
      }
      if(motionValue ==HIGH) {
  
  digitalWrite(buzzer, HIGH);
  
  }else  {
   
      digitalWrite(buzzer, LOW);
      
         }
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    lcd.setCursor(0,0);
    lcd.print(F("Error temp!"));
    Serial.println ("Error");
  }
  else {
    lcd.setCursor(0,0);
    lcd.print(F("Temp: "));
    lcd.setCursor(6,0);
    lcd.print(event.temperature);
    lcd.setCursor(11,0);
    lcd.print("C");
    Serial.println (event.temperature);
    
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    lcd.setCursor(0,1);
   lcd.println(F("Error humidity!"));
  }
  else {
    lcd.setCursor(0,1);
    lcd.print(F("Hum: "));
    lcd.setCursor(5,1);
    lcd.print(event.relative_humidity);
    lcd.setCursor(10,1);
    lcd.print("%");
    
  }
  if (event.temperature>=28.00) {
    digitalWrite (fan, HIGH);
  }
    else {
      digitalWrite (fan, LOW);
    }
    if (moistureValue>=800) {
    digitalWrite (pump, HIGH);
  }
    else {
      digitalWrite (pump, LOW);
    }
}

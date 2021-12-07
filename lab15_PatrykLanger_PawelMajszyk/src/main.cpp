#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#define LED_BUILTIN 14
#define DHTTYPE DHT11 // DHT 11
#define DHTPIN 5
#define ADCPIN 0
DHT dht(DHTPIN, DHTTYPE,50);
const int rs = 12, en = 13, d4 = 4, d5 = 0, d6 = 2, d7 = 14;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int nAdcReading = 0;
int nAD0 = analogRead(ADCPIN);
void printName(const char* str1, const char* str2) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(str1);
  lcd.setCursor(0,1);
  lcd.print(str2);
  delay(1000);
}
void readDhtValuesAndPrint(){
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();
  char buffer[16];
  char buffer1[16];
  sprintf(buffer, "Humidity:%2.1f%%Rh", hum);
  sprintf(buffer1, "Temp:%2.1f C", temp);
  printName(buffer,buffer1);
  delay(5000);
}
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  dht.begin();
  delay(1000);
  // printName("Patryk Langer","Pawel Majszyk");
  // delay(5000);
}
void writeButtonLabel(const int value){
  char buffer[16];
  sprintf(buffer, "%d", nAD0);
switch(value){
    case 1024:
      printName(buffer, "No button clicked!");
      break;
    case 780 ... 820:
      printName(buffer, "Button: Left!");
      break;
    case 220 ... 330:
      printName(buffer, "Button: Up!");
      break; 
    case 470 ... 550:
      printName(buffer, "Button: Down!");
      break; 
    case 0 ... 100:
      printName(buffer, "Button: Right!");
      break; 
    default:
      printName(buffer, "Something went wrong! :(");
      break;
  }
}

void loop() {
  nAD0 = analogRead(ADCPIN); 
  writeButtonLabel(nAD0);
}
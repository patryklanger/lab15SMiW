#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#define LED_BUILTIN 14
#define DHTTYPE DHT11 // DHT 11
#define DHTPIN 5
#define ADCPIN 0
//zdefiniowanie zmiennej przechowujacej informacje o czujniku dht11
DHT dht(DHTPIN, DHTTYPE,50);
const int rs = 12, en = 13, d4 = 4, d5 = 0, d6 = 2, d7 = 14;
//zdefiniowanie zmiennej przechowujacej informacje o ekranie lcd
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int nAdcReading = 0;
//zdefiniowanie zmiennej odczytujacej dzielnik napiecia z odpowiedniego pinu
int nAD0 = analogRead(ADCPIN);

/*
  Funkcja słuąca do wyświelania na ekranie dwoch lini tekstu
*/
void printTwoLinesOnDisplay(const char* firstLine, const char* secondLine) {
  //czyszcenie zawartości ekranu
  lcd.clear();
  //ustawianie kursora na pierwszy wiersz (początek wypisywania tekstu na ekranie)
  lcd.setCursor(0,0);
  //wypisanie na ekranie pierwszej linii tekstu
  lcd.print(firstLine);
  //ustawianie kursora na drugi wiersz (początek wypisywania tekstu)
  lcd.setCursor(0,1);
  //wypisanie na ekranie drugiej linii tekstu
  lcd.print(secondLine);
  //opoznienie wykonywania ekranu na 1000ms
  delay(1000);
}
/*
  Funkcja sluzaca do odczytania wartosci z czujnika i wypisaniu ich po odpowiednim sformatowaniu na ekran
*/
void readDhtValuesAndPrint(){
  //odczyt wilgotnosci z czujnika i zapsanie jej w zmiennej hum
  float hum = dht.readHumidity();
  //odczyt temperatury z czujnika i zapisanie jej w zmiennej temp
  float temp = dht.readTemperature();
  //stworzenie dwoch buforow w celu formatowania danych
  char buffer[16];
  char buffer1[16];
  //odpowienie formatowanie danych, zapisanie floatow do bufora zachowujac tylko jedna cyfre po przecinku
  sprintf(buffer, "Humidity:%2.1f%%Rh", hum);
  sprintf(buffer1, "Temp:%2.1f C", temp);
  //wyswietlenie wartosci na ekranie
  printTwoLinesOnDisplay(buffer,buffer1);
  //opoznienie programu o dodatkowe 4000ms (czyli w sumie 5000ms uwzgledniajac opoznienie w funkcji printTwoLinesOnDisplay)
  delay(4000);
}
void setup() {
  // put your setup code here, to run once:
  //inicjalizacja ekranu (16 znakow na linie, dwie linie tekstu)
  lcd.begin(16,2);
  //inicjalizacja czujnika dht11
  dht.begin();
  //wypisane imion i nazwisk na 3000ms po włączeniu urządzenia
  printTwoLinesOnDisplay("Patryk Langer","Pawel Majszyk");
  delay(2000);
}
/*
  Funkcja sluzaca do wypisania informacji o wcisnietym przycisku oraz wartosci, dla ktorej wcisniety przycisk zostal zidentyfikowany
*/
void writeButtonLabel(const int value){
  //definicja bufora
  char buffer[16];
  //wpisanie wartosci przekazanej do funkcji do bufora
  sprintf(buffer, "%d", value);
  //switch sprawdzajacy wartosc przekazana do funkcji i wypisujacy na ekranie odpowiednie labela dla konkretnego przycisku wraz z wartoscia (wartosci zostaly wczesniej sprawdzone manualnie)
switch(value){
    case 1024:
      printTwoLinesOnDisplay(buffer, "No button clicked!");
      break;
    case 780 ... 820:
      printTwoLinesOnDisplay(buffer, "Button: Left!");
      break;
    case 220 ... 330:
      printTwoLinesOnDisplay(buffer, "Button: Up!");
      break; 
    case 470 ... 550:
      printTwoLinesOnDisplay(buffer, "Button: Down!");
      break; 
    case 0 ... 100:
      printTwoLinesOnDisplay(buffer, "Button: Right!");
      break; 
    default:
      printTwoLinesOnDisplay(buffer, "Something went wrong! :(");
      break;
  }
}

void loop() {
  //odczytanie dzielnika napiecia z odpowiedniego pinu
  nAD0 = analogRead(ADCPIN); 
  writeButtonLabel(nAD0);
}
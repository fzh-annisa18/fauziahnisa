 #include <Wire.h>
#include <RTClib.h>
#include <SD.h>
#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <MQUnifiedsensor.h>
#include "variabel.h"
// Konfigurasi SD Card
File logFile;
// Konfigurasi RTC
RTC_DS3231 rtc;
// Konfigurasi Oled
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

MQUnifiedsensor MQ2("ESP32", Voltage_Resolution, ADC_Bit_Resolution, Pin, Type);

char timeString[20] = "";

float bacaGas(float a, float b) {
  MQ2.setA(a);
  MQ2.setB(b);
  MQ2.update();
  return MQ2.readSensor();
}
float gasKorek;
float gasAsapRokok;

void setup() {
  
  // Inisialisasi komunikasi serial
  Serial.begin(9600);
  while (!Serial) { ; }
  inisialisasi();
  display.clearDisplay();
  // Menampilkan semua bitmap satu per satu, tanpa mengulang
  logo();
}

void loop() {
  // Membaca data dari sensor gas
  sensorGas();
  // Membaca waktu dari RTC
  ambilWaktu();
    // Menulis data ke file SD
    simpanData();
  // Menampilkan informasi ke OLED
  display.clearDisplay();
  // Menampilkan judul "SENSOR GAS" di tengah layar
 tampilkanData();
  // Mengontrol LED dan buzzer
  if (gasKorek > 30.0 || gasAsapRokok > 60.0) {
    // Jika gas terdeteksi
    digitalWrite(LED_RED_PIN, HIGH);   // Nyalakan LED merah
    digitalWrite(LED_GREEN_PIN, LOW);  // Matikan LED hijau
    digitalWrite(BUZZER_PIN, HIGH);    // Nyalakan buzzer
  } else {
    // Jika gas tidak terdeteksi
    digitalWrite(LED_RED_PIN, LOW);     // Matikan LED merah
    digitalWrite(LED_GREEN_PIN, HIGH);  // Nyalakan LED hijau
    digitalWrite(BUZZER_PIN, LOW);      // Matikan buzzer
  }

  // Tunggu 1 detik sebelum membaca lagi
  delay(1000);
}
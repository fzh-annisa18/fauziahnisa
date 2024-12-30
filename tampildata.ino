#include "variabel.h"

 void tampilkanData(){
  sensorGas();
 int16_t x1, y1;
  uint16_t width, height;

  display.clearDisplay();  // Hapus layar sebelum menampilkan data

  display.setTextSize(1);  // Ukuran font 1
  display.setTextColor(SSD1306_WHITE);  // Warna teks putih
  
  // Menampilkan "SENSOR GAS" di tengah layar
  display.getTextBounds("SENSOR GAS", 0, 0, &x1, &y1, &width, &height);
  display.setCursor((SCREEN_WIDTH - width) / 2, 0);
  display.println("SENSOR GAS");

  // Menampilkan nilai Gas Korek
 // Koefisien untuk gas korek
  String gasKorekString = "Gas : " + String(gasKorek, 1) + " ppm";
  display.getTextBounds(gasKorekString, 0, 0, &x1, &y1, &width, &height);
  display.fillRect(0, 15, SCREEN_WIDTH, 8, SSD1306_BLACK); // Hapus area gas korek
  display.setCursor((SCREEN_WIDTH - width) / 2, 15);
  display.println(gasKorekString);

  // Menampilkan nilai Asap Rokok
 // Koefisien untuk asap rokok
  String gasAsapRokokString = "Asap Rokok: " + String(gasAsapRokok, 1) + " ppm";
  display.getTextBounds(gasAsapRokokString, 0, 0, &x1, &y1, &width, &height);
  display.fillRect(0, 30, SCREEN_WIDTH, 8, SSD1306_BLACK); // Hapus area asap rokok
  display.setCursor((SCREEN_WIDTH - width) / 2, 30);
  display.println(gasAsapRokokString);

  // Menampilkan waktu di tengah layar
  display.getTextBounds(timeString, 0, 0, &x1, &y1, &width, &height);
  display.fillRect(0, 45, SCREEN_WIDTH, 8, SSD1306_BLACK);
  display.setCursor((SCREEN_WIDTH - width) / 2, 45);
  display.println(timeString);

  display.display(); 
 }
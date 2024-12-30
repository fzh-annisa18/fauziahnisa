#include "variabel.h"
void inisialisasi () {
  // Inisialisasi LED dan buzzer
    pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT );
  pinMode(BUZZER_PIN, OUTPUT);

  // Inisialisasi kartu SD
  Serial.print("Menginisialisasi kartu SD...");
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("Inisialisasi kartu SD gagal!");
    while (1);
  }
  Serial.println("Kartu SD berhasil diinisialisasi.");

  // Membuat atau membuka file log
  logFile = SD.open("/data_log.txt", FILE_APPEND);
  if (logFile) {
    logFile.println("Waktu, Nilai Gas"); // Header file
    logFile.close();
    Serial.println("File log berhasil dibuat/dibuka.");
  } else {
    Serial.println("Gagal membuka file log.");
  }

  //inisialisasi rtc
  if (!rtc.begin()) {
    Serial.println("RTC tidak terdeteksi!");
    while (1);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC kehilangan daya, mengatur ulang waktu.");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Inisialisasi OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Pastikan alamat I2C sesuai
    Serial.println(F("OLED tidak terdeteksi!"));
    while (1);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
MQ2.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ2.init();

  Serial.print("Kalibrasi, harap tunggu");
  float calcR0 = 0;
  for (int i = 1; i <= 10; i++) {
    MQ2.update(); // Update data, baca tegangan dari pin analog
    calcR0 += MQ2.calibrate(RatioMQ2CleanAir);
    Serial.print(".");
  }
  MQ2.setR0(calcR0 / 10);
  Serial.println(" Selesai!");

  if (isinf(calcR0)) {
    Serial.println("Peringatan: Koneksi bermasalah, R0 tidak terdefinisi. Periksa wiring!");
    while (1);
  }
  if (calcR0 == 0) {
    Serial.println("Peringatan: Koneksi bermasalah, R0 = 0. Periksa wiring!");
    while (1);
  }
}
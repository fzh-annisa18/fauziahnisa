#include "variabel.h"
#include <RTClib.h>
#include <SD.h>

// Variabel global
DateTime lastLogDate; // Untuk mencatat tanggal terakhir log

void simpanData() {
    // Perbarui data sensor dan waktu
    sensorGas();
    ambilWaktu();

    // Waktu sekarang dalam milidetik
    unsigned long currentTime = millis();

    // Dapatkan waktu sekarang dari RTC
    DateTime now = rtc.now();

    // Periksa apakah sudah hari baru
    if (!lastLogDate.isValid() || now.day() != lastLogDate.day()) {
        // Tulis pembatas ke file log
        logFile = SD.open("/DataGas_log.txt", FILE_APPEND);
        if (logFile) {
            logFile.println(); // Baris kosong untuk pemisah
            logFile.println("===== LOG BARU =====");
            logFile.print("Tanggal: ");
            logFile.println(now.timestamp(DateTime::TIMESTAMP_DATE));
            logFile.close();
        }
        lastLogDate = now; // Perbarui tanggal terakhir log
    }

    // Periksa apakah sudah lebih dari 10 menit sejak log terakhir
    if (currentTime - lastLogTime >= logInterval) {
        // Perbarui waktu terakhir data disimpan
        lastLogTime = currentTime;

        // Simpan data ke SD card
        logFile = SD.open("/DataGas_log.txt", FILE_APPEND);
        if (logFile) {
            // Format penyimpanan: Waktu, LPG, AsapRokok
            logFile.print(now.timestamp(DateTime::TIMESTAMP_DATE));
            logFile.print(" ");
            logFile.print(now.timestamp(DateTime::TIMESTAMP_TIME));
            logFile.print(", ");
            logFile.print("LPG=");
            logFile.print(gasKorek);
            logFile.print(", ");
            logFile.print("AsapRokok=");
            logFile.println(gasAsapRokok);
            logFile.close();

            // Serial monitor output
            Serial.print("Data disimpan: ");
            Serial.print(now.timestamp(DateTime::TIMESTAMP_DATE));
            Serial.print(" ");
            Serial.print(now.timestamp(DateTime::TIMESTAMP_TIME));
            Serial.print(", LPG=");
            Serial.print(gasKorek);
            Serial.print(", AsapRokok=");
            Serial.println(gasAsapRokok);
        } else {
            Serial.println("Gagal membuka file untuk menulis.");
        }
    }
}

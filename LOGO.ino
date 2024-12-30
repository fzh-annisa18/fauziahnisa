void logo(){
for (int i = 0; i < 46; i++) {
    Serial.print("Menampilkan bitmap ke-");
    Serial.println(i);
    display.clearDisplay(); // Membersihkan layar sebelum menggambar
    display.drawBitmap(0, 0, myBitmapallArray[i], 128, 64, SSD1306_WHITE);
    display.display();
    delay(100);
}
}
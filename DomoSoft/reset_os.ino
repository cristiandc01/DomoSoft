void HardReset() {
  for (int i = 0; i < 360; ++i) {
    EEPROM.write(i, 0);
  }

  Main = SPIFFS.open("/device_name", "w");
  Main.print("DomoSoft device");
  Main.close();
  delay(200);
  Main = SPIFFS.open("/discovery/prefix", "w");
  Main.print("homeassistant");
  Main.close();
  delay(200);
  WiFi.disconnect(true);

}

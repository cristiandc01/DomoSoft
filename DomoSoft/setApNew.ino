void setAP() {



  if (EEPROM.read(200) == 255) {
    delay(1000);
    for (int i = 0; i < 360; ++i) {
      EEPROM.write(i, 0);
    }
    EEPROM.commit();
    delay(500);
    WiFi.disconnect();
    ESP.restart();
  }




  WiFiManager wifiManager;

  wifiManager.startConfigPortal(deviceAP);


  EEPROM.write(200, 1);
  EEPROM.commit();
  bootConfig();

  Serial.print("WIFI IP: ");
  Serial.println(WiFi.localIP());
  IPaddress =  WiFi.localIP().toString();
  ESP.restart();

}

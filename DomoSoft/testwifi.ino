
bool testWifi(void) {
  if (bootMode == 0) {
    if (EEPROM.read(200) == 1) {
      if (WiFi.SSID() == "") {
        return false;
      }
      int c = 1;
      Serial.println("Waiting for Wifi to connect");

      while (c) {
        if (WiFi.status() == WL_CONNECTED) {
          normalset();

          return true;

        }

        delay(500);
        char read = Serial.read();
        switch (read) {
          case '*':
            EEPROM.write(200, 0);
            EEPROM.commit();
            ESP.restart();


        }
      }

      return false;
    } else {
      mqtt_conf = 0;
      Serial.println("NEW USER, opening AP");
      return false;
    }


  } else {
    mqtt_conf = 0;
    EEPROM.write(bootMode_add, 0);
    EEPROM.commit();
    return false;
  }
}

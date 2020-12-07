void Ricevi() {
  while (Serial.available()) {
    char car = Serial.read();
    ricevuto = 1;
    SerialData = SerialData + car;
  }
  if (ricevuto) {
  if (SerialData == "TEST") {
    Serial.print("OK");
    SerialData = "";
    ricevuto = 0;
  }
  else if (SerialData == "DomoSoft") {
    String l = String(DomoSoft) + " Build: " + String(build);
    Serial.print(l);
    SerialData = "";
    ricevuto = 0;
  }




  else {
    SerialData = "";
    ricevuto = 0; Serial.print("ERRORE");
  }
}
}

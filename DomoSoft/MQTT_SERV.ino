

bool mqtt_conn() {


  if (client.connect(String(devname).c_str(), String(mqtt_user).c_str(), String(mqtt_password).c_str())) {
    //Serial.println("connected");
    client.setCallback(callback);
 //   client.subscribe(rele1_control_topic.c_str());
  // SUBSCRIBE HEERE 
    
    MQTT_sync();
  }
  return client.connected();
}


void callback(String topic, byte* payload, unsigned int length) {
  String messaggio;
  // Serial.print("Message arrived [");
  // Serial.print(topic);
  // Serial.println("] ");

  for (int i = 0; i < length; i++) {

    messaggio += (char)payload[i];
  }
  delay(100);

// if topic==  put here the check
  

  

}

void MQTT_sync() {
//  client.publish(rele1_status_topic.c_str(), String(rele1S).c_str(), true);
  
  

}

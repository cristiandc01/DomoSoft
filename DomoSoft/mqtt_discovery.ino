void discover() {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["name"] = devname;
 // json["command_topic"] = rele1_control_topic;
  //json["state_topic"] = rele1_status_topic;
  json["payload_off"] = "0";
  json["payload_on"] = "1";

  String topic = hassio_prefix + "/" + "switch" + "/domosoft4/" + ESP.getFlashChipId()  + "1" + "/config";
  char JSONmessageBuffer[512];
  json.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));



  client.publish(topic.c_str(), JSONmessageBuffer, true);
  discovered = 1;
  EEPROM.write(201, discovered);
  EEPROM.commit();
}


void deleteConfig() {
  String topic = hassio_prefix + "/" + "switch" + "/domosoft4/" + ESP.getFlashChipId()  + "1" + "/config";
  client.publish(topic.c_str(), "", true);
  discovered = 0;
  EEPROM.write(201, discovered);
  EEPROM.commit();
}


//  String message = "{'name':'" + devname + "','command_topic':'" + rele1_control_topic + "','state_topic':'" + rele1_status_topic + "','payload_off':'0','payload_on':'1'}";

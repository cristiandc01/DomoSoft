//webserver for domosoft

#define  DomoSoft  "4.3"
//#define  RelaySoft  "2.0"
#define  build "DSF-06062020"

String  version = String(DomoSoft) + " <br>" + "<br>Build: " + String(build);

#define deviceAP "DomoSoft"

//#define NTP_ENABLED

#include <WiFiManager.h>
int isUpdate = 0;
#include <PubSubClient.h>
#include "FS.h"
#include <ArduinoJson.h>
#include <StreamString.h>
#include <ESP8266HTTPClient.h>
#include <EEPROM.h>
#include <ESP8266HTTPUpdateServerDomoSoft.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>

#ifdef NTP_ENABLED
#include <WiFiUdp.h>
#include <NTPClient.h>
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "it.pool.ntp.org", 7200, 60000);
#endif

String deviceID = "";
String MyApiKey = "";
int wifi_ok;
File Main;
bool isConnected = false;

String hassio_prefix = "homeassistant";

// MQTT variabili ----------------------------
String mqtt_server = "";
String mqtt_user = "";
String mqtt_password = "";

String IPaddress;

String devname;
String devname2;



long sync;
long lastReconnectAttempt = 0;



byte E_MQ = 0;

String text;
char car;
int printa = 0;










String SerialData;
long serialBaud = 115200;
byte ricevuto;

MDNSResponder mdns;
byte mqtt_conf = 1;
String st;
String content;
int statusCode;


byte discovered = 0;

//SICUREZZA

String username = "";
String password = "";
const char* realm = "DomoSoft";

//Bootloader
byte bootMode_add = 97;
byte bootMode = 0;

//this ssid and Password is for Hotspot connection

WiFiClient httpclient;
ESP8266WebServer server(80);
PubSubClient client(httpclient);
ESP8266HTTPUpdateServer httpUpdater;

DNSServer dnsServer;
IPAddress apIP(192, 168, 1, 1);
const byte DNS_PORT = 53;

void setup(void) {
  EEPROM.begin(512);
  SPIFFS.begin();
  if (SPIFFS.exists("/settings/serial_baud")) {
    Main = SPIFFS.open("/settings/serial_baud", "r");
    String ciaoF;
    while (Main.available()) {
      ciaoF += char(Main.read());
    }
    Main.close();
    serialBaud = ciaoF.toInt();
    Serial.begin(serialBaud);
  } else {
    Serial.begin(serialBaud);
  }

  Serial.println();
  Serial.println("--------DC DOMOTICS--------");
  Serial.println("--------DOMOSOFT 4.2--------");
  Serial.println(version);
  Serial.println();
  delay(100);
  bootMode = EEPROM.read(bootMode_add); //read bootMode

  if (!SPIFFS.exists("/Config_ok")) {
    delay(3000);
    Serial.println("ERRORE 02: FileSystem danneggiato! Ricaricare correttamente il firmware.");
    ESP.deepSleep(  ESP.deepSleepMax(), WAKE_RF_DISABLED);
  }

  WiFi.mode(WIFI_STA);

  WiFi.hostname("DomoSoft");

  // Serial.println();
  //Serial.println();
  //Serial.println("Avvio");


  for (int i = 166; i < 181; ++i)
  {
    username += char(EEPROM.read(i));

  }

  for (int i = 181; i < 199; ++i)
  {
    password += char(EEPROM.read(i));

  }

  mqtt_conf = EEPROM.read(202);









  if (testWifi()) {
    bootConfig();

    Serial.print("WIFI IP: ");
    Serial.println(WiFi.localIP());
    IPaddress =  WiFi.localIP().toString();
    return;
  }
  setAP();
  // setupAP();



}

void loop(void) {
#ifdef NTP_ENABLED
  timeClient.update();
#endif
  if (mqtt_conf == 1) {
    client.loop();
    if (!client.connected()) {
      long now = millis();
      if (now - lastReconnectAttempt > 30000) {
        lastReconnectAttempt = now;
        E_MQ = 1;
        // Attempt to reconnect
        if (mqtt_conn()) {
          lastReconnectAttempt = 0;
          E_MQ = 0;
        }
      } else {
        client.loop();
      }


    }
  }




  server.handleClient();

  if (wifi_ok == 0) {
    dnsServer.processNextRequest();
    Ricevi();
  }



}

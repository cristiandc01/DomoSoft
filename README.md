# DomoSoft

Domosoft allows the control of domotic devices with ESP chips through the HTTP protocol (with web page) and also with the MQTT protocol.

this repository contains the essential part of domosoft. it can be easily downloaded and consulted as well as editable and shared according to the license described.

# How to Build 

To build DomoSoft you need the pre-installed Arduino IDE with the libraries and additional devices installed inside: ESP8266-Arduino board list.
Link: https://github.com/esp8266/Arduino

# The Structure


The domosoft FLASH structure is divided into 3 parts:

  - SKETCH:
    This part contains all the DomoSoft code.
   
  - EEPROM: 
    Here DomoSoft saves some of its settings and environment variables.
    
  - SPIFFS:
    This section contains all the HTML pages reproduced by the webserver. it also contains some settings which, due to space / OEM pre-modification, cannot be saved on the EEPROM.

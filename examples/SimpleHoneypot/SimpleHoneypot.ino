/*
ESPCanary by AnotherMaker
This script will turn an ESP8266 or an ESP32 into a honeypot FTP server.

After setting your basic configuration below, this script will join your network and present
itself as a standard FTP server (Synology). If someone connects to it using the username admin and
ANY password, it will hit a webhook.  Most people will just want to go to https://opencanary.org
and generate a free "Web Bug/URL token" and paste that url below. This token will automatically email you when someone hits the FTP server.

If you want to get a little fancier, you can setup your own webhook url on your own server and
ESPCanary will POST the ip address that tried to access the FTP server to that webhook.

You can also use the SPIFFS file system to upload typical honeypot type files such as fake API keys and anything else you can get creative and generate.
*/

#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif defined ESP32
#include <WiFi.h>
#include <esp_wifi.h>
#include "SPIFFS.h"
#endif

#include <ESPCanary.h>


// if you would like to create your own mac address for your canary...
// by default we're using a Synology mac address (0x00, 0x11, 0x32)
// must be unique per network
uint8_t newMACAddress[] = {0x00, 0x11, 0x32, 0x07, 0x0D, 0x66};

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASS";
String canary = "PASTE_CANARY TOKEN HERE";  //grab FREE web bug/URL tokens at http://canarytokens.org
String ftp_user = "admin";    //if you replace this with "%" it will accept ANY username
String ftp_pass = "password"; //if you replace this with "%" it will accept ANY password
bool append_ip = false;       //if you are using a canary token, leave this as false
String append_char = "?";     //if you are using a canary token, this doesn't matter
                              //if you are using your own webhook,with a bunch of GET
                              //parameters then you would want this to be "&" so the IP
                              //address becomes the final GET parameter

FtpServer ftpSrv;   //set #define FTP_DEBUG in ESPCanary.h to see ftp verbose on serial

void setup(void){
  Serial.begin(115200);

  #ifdef ESP8266
    wifi_set_macaddr(STATION_IF, &newMACAddress[0]);
  #elif defined ESP32
    WiFi.mode(WIFI_STA);
    esp_wifi_set_mac(ESP_IF_WIFI_STA, &newMACAddress[0]);
  #endif

  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }


  Serial.println("");
  // Serial.print("Connected to ");
  // Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());

  /////FTP Setup, ensure SPIFFS is started before ftp;  /////////
  #ifdef ESP32       //esp32 we send true to format spiffs if cannot mount
    if (SPIFFS.begin(true)) {
  #elif defined ESP8266
    if (SPIFFS.begin()) {
  #endif
        Serial.println("SPIFFS opened!");
        ftpSrv.begin(ftp_user,ftp_pass,canary,append_ip,append_char);    //username, password for ftp.  set ports in ESPCanary.h  (default 21, 50009 for PASV)
    }
}

void loop(){
  ftpSrv.handleFTP();        //make sure in loop you call handleFTP()!!
 // server.handleClient();   //example if running a webserver you still need to call .handleClient();
}

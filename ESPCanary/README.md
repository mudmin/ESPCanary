# ESPCanary
Use an ESP8266 or ESP32 as an FTP server to detect that someone is snooping around your network.

To use it in its most basic form, create a free "Web Bug/URL token" at http://canarytokens.org/generate and paste it in your sketch as the "canary" variable.

When someone connects to the FTP server, you will receive a near instantaneous email warning you that
someone is snooping.  For a little bit more advanced tracking, use the other canary tokens and upload them to the SPIFFS of the ESP board and let the hacker download them and trigger them.

Note that although it looks like users can upload and rename the files on your FTP server, that's all smoke and mirrors. Those changes are flushed away when the user reloads the files and are never actually present on the ESP.  

To connect to the ESP over FTP, grab the ip from the serial monitor and connect with admin, any password, port 21.  You may have to check a box to allow insecure connections.

I'm clearly not a C developer if you want to contribute and help make this project better! 

This is a fork of the https://github.com/nailbuster/esp8266FTPServer library by David Paiva.

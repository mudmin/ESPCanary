# ESPCanary
Use an ESP8266 or ESP32 as an FTP server to detect that someone is snooping around your network.

To use it in its most basic form, create a free "Web Bug/URL token" at http://canarytokens.org/generate and paste it in your sketch as the "canary" variable.

When someone connects to the FTP server, you will receive a near instantaneous email warning you that
someone is snooping.  For a little bit more advanced tracking, use the other canary tokens and upload them to the SPIFFS of the ESP board and let the hacker download them and trigger them.

Note that although it looks like users can upload and rename the files on your FTP server, that's all smoke and mirrors. Those changes are flushed away when the user reloads the files and are never actually present on the ESP.  

When you configure your FTP server, you can choose to specify a username and/or password that is allowed
to connect to the server or substitute % for either of those so that any string will do!

To connect to the ESP over FTP, grab the ip from the serial monitor and connect with your username and password along with port 21.  You may have to check a box to allow insecure connections.

When someone connects to your FTP server, it will fire off the canary and you will get an email. In that
email, the Source IP will be the IP of your server and the User Agent will be the IP address of the
incoming connection to your server.  

If you do not want to use canarytokens.org, you can specify any webhook url and the offending IP
can be appended to your query string as an additional parameter.

I'm clearly not a C developer if you want to contribute and help make this project better!

This is a fork of the https://github.com/nailbuster/esp8266FTPServer library by David Paiva.
Thanks to the people at https://thinkst.com for offering tech support and providing canary tokens for free.

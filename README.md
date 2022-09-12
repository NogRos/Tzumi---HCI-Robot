# Tzumi---HCI-Robot
Tzumi is a robot based on ESP8266 that helps families be more focused on each other during dinner times.
 This project is constructed of 3 main parts:
 - accelToHttp - 
A javascript project that allows connecting to tzumi app on the phone...
 - HttpToMqttBroker - 
A python broker that recieves HTTP GET requests and sends MQTT messages to Esp8266...
 - tzumi-Esp8266-code - 
A C++ project that runs on the Esp8266 to recieve MQTT messages and act accordingly...

Thanks to Omer Erman my R&D partner for this project.

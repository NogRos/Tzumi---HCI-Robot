// MQTT Broker
const char *mqtt_broker = "broker.emqx.io";
const char *topic = "tzumi/mqtt";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 1883;

int PHONE_DOWN = 0;
int PHONE_UP = 1;

int FLAG_FOR_MOVEMENT = PHONE_DOWN;
char movementDetection = '0';

WiFiClient espClient;
PubSubClient client(espClient);

void printMessage(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char) payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");
}

//reads input message and updates flag
void callback(char *topic, byte *payload, unsigned int length) {
  printMessage(topic, payload, length);
  movementDetection = (char) payload[0];

  if (movementDetection != '0' && movementDetection != '1') {
    movementDetection = '0';  //IF INVALID INPUT - DON'T SPIN
  }
  /*    FOR PHYPHOX - ACCELEROMETER
  if (movementDetection == (char)'M' && FLAG_FOR_MOVEMENT == PHONE_DOWN) {
    FLAG_FOR_MOVEMENT = PHONE_UP;
    delay(15);
  }
  if (movementDetection == (char)'D' && FLAG_FOR_MOVEMENT == PHONE_UP) {
    FLAG_FOR_MOVEMENT = PHONE_DOWN;
    delay(15);
  }
  */
}



//used only in setup to connect - DO NOT TOUCH
void connectAsMQTTClient() {
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
    String client_id = "esp8266-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Public emqx mqtt broker connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  // publish and subscribe
  client.publish(topic, "hello emqx");
  client.subscribe(topic);
}

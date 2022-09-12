#include <Stepper.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "mqtt_broker.h";
#include "wifi_conf.h";
#include "stepper.h";
#include "Adafruit_MPR121.h"
#include "speed_controller.h";
#include "MPR121.h";
/////////////////////////////////////

//bool UP = 0; //flag to recognize occurance only once at a time
//bool DOWN = 0;//flag to recognize occurance only once at a time
//bool motor_is_spinning = false; // flag for motor
//int nextSpeedIndex;
int motorPin = D4; //motor transistor is connected to pin 3
int ANGRY_TZUMI = 0;
unsigned long prevMillis = 0;

void setup() {
  pinMode(motorPin, OUTPUT);
  yield();
  Serial.begin(9600);
  connectToWifi();
  connectAsMQTTClient();
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");
  yield();
  Serial.println("finished setup");
}

void loop() {
  unsigned long currentMillis = millis();
  //to recieve MQTT broker messages
  client.loop();
  yield();

  //START SPINNING IF INPUT IS '1' AND NOT SPINNING ALREADY
  if (movementDetection == '1' && SPINNING == 0) {
    SPINNING = 1;
    prevMillis = currentMillis;
    yield();
  }

  if (SPINNING) {

    if (currentMillis - prevMillis > 5000) {
      ANGRY_TZUMI = 1;
      //Serial.println("ANGRY!!");
    }
      //STEPPER ADVANCES
      myStepper.step(1);
      yield();
      //Serial.println(speeds[speed_index]);
      delay(speeds[speed_index] - (ANGRY_TZUMI * kick_for_tzumi));
      //Serial.println(speeds[speed_index]);
      yield();
      delayMicroseconds(1500);

      //CHECK TOUCHES
      detect_touches();
      yield();
      sumButtons = buttons[0] + buttons[1] + buttons[2] + buttons[3];
      speed_index = sumButtons;

      if (speed_index > 0) {
        prevMillis = currentMillis;
      }
      
      yield();
      //Serial.print(speed_index);
      //Serial.println("  touches");
      lasttouched = currtouched;

      //CHECK THAT ALL TOUCHED - STOP SPINNING
    if (speed_index == 4) {
      SPINNING = 0;
      movementDetection = '0';
      ANGRY_TZUMI = 0;
      yield();
        digitalWrite(motorPin, HIGH); //vibrate
        delay(400);  // delay one second
        digitalWrite(motorPin, LOW);  //stop vibrating
        yield();
        //Serial.println("supposed to vibrate");
      }
  }

  //  return;
  //  error_message_MPR121();
}



//activated when phone up and this is the first time since it was down
//void checkPhoneUpMovement() {
// if (FLAG_FOR_MOVEMENT == PHONE_UP && UP == 0) {
//  UP = 1;
//    DOWN = 0;
//    Serial.println("phone up!!!");
//    delay(15);
// }
//}

//activated when phone down and this is the first time since it was up
//void checkPhoneDownMovement() {
// if (FLAG_FOR_MOVEMENT == PHONE_DOWN && DOWN == 0) {
//   UP = 0;
//   DOWN = 1;
//  Serial.println("phone down!!!");
//   delay(15);
//}
//}

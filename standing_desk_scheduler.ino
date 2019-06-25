/*
 * Something good for your health :)
 * This is to schedule intervals for the standing desk's states.
 * The time sitting and standing and the time it takes for the desk to reach the desired height 
 * can be configured bellow.
 * 
 * Hardware:
 * - Arduino Uno clone
 * - HC-SR04 Ultrasonic Sensor
 * - Dual Relay module
 * - Standing desk with a DC motor powered with a 30V/2A adapter
 * - plugs and wires
 * 
 * The state of the desk is stored in the EEPROM 
 * and whenever the user restarts the Arduino, the desk state will toggle.
 */

#include "NewPing.h"

#define BUTTON 12
#define LED 13
#define CW 7
#define CCW 8

#define TRIGGER_PIN 3
#define ECHO_PIN 4
#define MAX_DISTANCE 200

static const float GET_UP_DISTANCE = 50; // [cm]
static const float GET_DOWN_DISTANCE = 7; // [cm]
bool toggle = true;
bool internalToggle = true;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  pinMode(CW, OUTPUT);
  pinMode(CCW, OUTPUT);

  Serial.begin(9600);
  
}

void loop() {
   int buttonValue = digitalRead(BUTTON);
   
   if (buttonValue == LOW){
      if (toggle) {
        // GET UP
        while (getDistance() < GET_UP_DISTANCE) {
          
          //Serial.print("Distance = ");
          //Serial.println(getDistance());
      
          digitalWrite(LED,HIGH);
          digitalWrite(CCW, HIGH);
        }
      } else {
        // GET DOWN
        while (getDistance() > GET_DOWN_DISTANCE) {
          
          //Serial.print("Distance = ");
          //Serial.println(getDistance());
      
          digitalWrite(CW,HIGH);
        }
      }
      internalToggle = true;
      
   } else if (internalToggle) {
        toggle = !toggle;
        internalToggle = false;
        digitalWrite(LED, LOW);
     
        digitalWrite(CW, LOW);
        digitalWrite(CCW, LOW);
    } else {
      // do nothing
    }
}

float getDistance() {
    // Send ping, get distance in cm
    const float distance = sonar.ping_cm();
    const float duration = sonar.ping_median(5);
    return (duration / 2) * 0.0343;
} 

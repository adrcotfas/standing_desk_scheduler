/*
 * Something good for your health :)
 * This is to schedule intervals for the standing desk's states.
 * The time sitting and standing and the time it takes for the desk to reach the desired height 
 * can be configured bellow.
 * 
 * Hardware:
 * - Arduino Uno
 * - L298N motor driver
 * - Standing desk with a DC motor powered with a 30V/2A adapter
 * - plugs and wires
 * 
 * The state of the desk is stored in the EEPROM 
 * and whenever the user restarts the Arduino, the desk state will toggle.
 */

#include <EEPROM.h>

static const unsigned long timeSitting  = 60 /*[minutes]*/ * 60000; // [ms]
static const unsigned long timeStanding = 20 /*[minutes]*/ * 60000; // [ms]
static const unsigned long timeToToggle = 5000; // [ms] 

static const int deskIsUpAdress = 0;

static const int enA = 10;
static const int in1 = 9;
static const int in2 = 8;

bool deskIsUp;
static unsigned long lastToggleTime = 0;

void setup() {

  //TODO: delete this after debugging
  Serial.begin(9600);
  
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  EEPROM.get(deskIsUpAdress, deskIsUp);

  //TODO: delete this after debugging
  Serial.print("deskIsUp: ", deskisUp);
}

void loop() {
  if ((lastToggleTime == 0) ||
      (deskIsUp && ((millis() - lastToggleTime) > timeStanding)) ||
      (!deskIsUp && ((millis() - lastToggleTime) > timeSitting))) {
    deskIsUp = !deskIsUp;
    EEPROM.put(deskIsUpAdress, deskIsUp);
    toggleDesk();
    lastToggleTime = millis();
  }
}

void toggleDesk() {
  //TODO: delete this after debugging
  Serial.print("toggleDesk");
  
  digitalWrite(in1, deskIsUp ? HIGH : LOW);
  digitalWrite(in2, deskIsUp ? LOW : HIGH);
  analogWrite(enA, 200);
  delay(timeToToggle);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);
}

// credentials for connecting to Blynk cloud
#define BLYNK_TEMPLATE_ID "TMPL39gKg3JMg"
#define BLYNK_TEMPLATE_NAME "Raining"
#define BLYNK_AUTH_TOKEN "vwAGgfVLJl4KKRL-A8z2XBDt-b5QPGig"

#define BLYNK_PRINT Serial  // to print statements on serial monitor terminal

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>


#define POWER_PIN D7  // The ESP8266 pin that provides the power to the rain sensor
#define DO_PIN D2     // The ESP8266 pin connected to DO pin of the rain sensor
#define RAIN_SENSOR_PIN A0
#define RAIN_SENSOR_THRESHOLD 800

Servo servo;  // creatiing servo object

char ssid[] = "POCO M2 Pro";
char pass[] = "amishac2003";

void setup() {
  // Initialize the Serial to communicate with the Serial Monitor.
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // initialize the ESP8266's pin as an input
  pinMode(POWER_PIN, OUTPUT);  // Configure the power pin pin as an OUTPUT
  pinMode(DO_PIN, INPUT);
  servo.attach(2);  //attaching servo motor to D4
  servo.write(0);   //setting servo motor's angle at 0 deg
}

void loop() {
  digitalWrite(POWER_PIN, HIGH);  // turn the rain sensor's power  OFF
  delay(10);                      // wait 10 milliseconds

  int rain_state = digitalRead(DO_PIN);   // read value from D2 pin coming from rain sensory

  digitalWrite(POWER_PIN, LOW);  // turn the rain sensor's power ON

  int sensorValue = analogRead(RAIN_SENSOR_PIN);

  if (rain_state == HIGH) {
    Serial.println("The rain is NOT detected");
    servo.write(0);  // tell servo to rotate to 0 deg
    delay(10);       // waits 10ms for the servo to reach the position
  } else {
    Serial.println("The rain is detected");
    // rotate from 180 degrees to 0 degrees
    servo.write(180);  // tell servo to rotate to 180 deg
    delay(10);         // waits 10ms for the servo to reach the position
  }
  delay(1000);  // pause for 1 sec to avoid reading sensors frequently to prolong the sensor lifetime

  if (sensorValue < RAIN_SENSOR_THRESHOLD) {
    Blynk.logEvent("its_raining");
  }

  Blynk.virtualWrite(V0, sensorValue);

  Blynk.run();
}

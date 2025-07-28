#include <Arduino.h>
#include<PubSubClient.h>
#include <WiFi.h>
#include ".env.h"

WiFiClient client;
PubSubClient mqtt(client);
volatile bool first_signal = true;
volatile bool isMotionDetected = false;
volatile int motionCount = 0;
String message = "";
String Answer[Ansarray_SIZE];
bool thrump_finger_bend()
{
  int thrump_adc = analogRead(thrump_finger);
  if (thrump_adc >= 4000) {
    // Serial.println("Thrump finger is bent");
    return true;
  }
  return false;
}

bool index_finger_bend()
{
  int index_adc = analogRead(index_finger);
  if (index_adc >= 4000) {
    // Serial.println("Index finger is bent");
    return true;
  }
  return false;
}

bool middle_finger_bend()
{
  int middle_adc = analogRead(middle_finger);
  if (middle_adc >= 4000) {
    // Serial.println("Middle finger is bent");
    return true;
  }
  return false;
}

bool ring_finger_bend()
{
  int ring_adc = analogRead(ring_finger);
  if (ring_adc >= 4000) {
    // Serial.println("Ring finger is bent");
    return true;
  }
  return false;
}

bool little_finger_bend()
{
  int little_adc = analogRead(little_finger);
  if (little_adc >= 4000) {
    // Serial.println("Little finger is bent");
    return true;
  }
  return false;
}

String prediction()
{
  if(thrump_finger_bend() && !index_finger_bend() && middle_finger_bend() && ring_finger_bend() && little_finger_bend())
  {
    Serial.println("one");
    return "One";
  }
  else if(thrump_finger_bend() && !index_finger_bend() && !middle_finger_bend() && ring_finger_bend() && little_finger_bend())
  {
    Serial.println("two");
    return "Two";
  }
  else if(!thrump_finger_bend() && !index_finger_bend() && !middle_finger_bend() && ring_finger_bend() && little_finger_bend())
  {
    Serial.println("three");
    return "Three";
  }
  else if(!thrump_finger_bend() && !index_finger_bend() && !middle_finger_bend() && !ring_finger_bend() && little_finger_bend())
  {
    Serial.println("four");
    return "Four";
  }
  else if(!thrump_finger_bend() && !index_finger_bend() && !middle_finger_bend() && !ring_finger_bend() && !little_finger_bend())
  {
    Serial.println("five");
    return "Five";
  }
  else if(!thrump_finger_bend() && index_finger_bend() && middle_finger_bend() && ring_finger_bend() && !little_finger_bend())
  {
    Serial.println("six");
    return "Six";
  }
  else if(!thrump_finger_bend() && index_finger_bend() && middle_finger_bend() && !ring_finger_bend() && !little_finger_bend())
  {
    Serial.println("seven");
    return "Seven";
  }
  else if(!thrump_finger_bend() && index_finger_bend() && middle_finger_bend() && !ring_finger_bend() && little_finger_bend())
  {
    Serial.println("eight");
    return "Eight";
  }
  else if(!thrump_finger_bend() && index_finger_bend() && !middle_finger_bend() && ring_finger_bend() && little_finger_bend())
  {
    Serial.println("nine");
    return "Nine";
  }
  else if(thrump_finger_bend() && index_finger_bend() && middle_finger_bend() && ring_finger_bend() && little_finger_bend())
  {
    Serial.println("ten");
    return "Ten";
  }
  else
  {
    Serial.println("unknown");
    return "Unknown";
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Setup complete");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
}

void loop() {
  int value_thrump = analogRead(thrump_finger);
  int value_index = analogRead(index_finger);
  int value_middle = analogRead(middle_finger);
  int value_ring = analogRead(ring_finger);
  int value_little = analogRead(little_finger);

  Serial.print("Thumb: ");
  Serial.print(value_thrump);
  Serial.print(", Index: ");
  Serial.print(value_index);
  Serial.print(", Middle: ");
  Serial.print(value_middle);
  Serial.print(", Ring: ");
  Serial.print(value_ring);
  Serial.print(", Little: ");
  Serial.println(value_little);
  Serial.println("===============Result===============");
  Serial.println(prediction());
  Serial.println("===============End===============");

  delay(5000);
}


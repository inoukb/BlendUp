/*
 * Derivate from reaDIYmate pusher example. Connects to a WiFi signal (status Led
 * Green when connected, Red if not) and wait for a pusher.com message to switch
 * On or off a relay (status led orange when receiving pusher message).
 *
 * To be able to build and upload this sketch to a reaDIYmate board:
 * - Add avr-libraries from https://github.com/reaDIYmate to your Arduino libraries
 * - Download and add SdFat lib to your Arduino "libraries" directory
 * - From https://github.com/reaDIYmate/avr-arduino add content of 'cores' and 
 * 'variants' to /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino
 * and from boards.txt get reaDIYmate board profile and add it to your boards.txt 
 */
 
#include <Api.h>
#include <Audio.h>
#include <BufferedStream.h>
#include <digitalWriteFast.h>
#include <Download.h>
#include <ExtendedStream.h>
#include <HttpClient.h>
#include <JsonStream.h>
#include <PusherClient.h>
#include <SerialStream.h>
#include <Sha256.h>
#include <StatusLed.h>
#include <Vs1011.h>
#include <Wifly.h>
#include <SdFat.h>

boolean blender = false; // Blender On-Off

// Buffer to store data retrieved from Pusher
char buffer[2048];
PusherClient pusher(wifly, buffer, 2048);

// RN171 module WiFi connectivity: pass serial port and pin number to constructor
Wifly wifly = Wifly(Serial1, 49, 74, 75, 76);

StatusLed led = StatusLed(78,79); // ReaDIYmate status Led

void setup() {
    pinMode(3, OUTPUT);    // blender's relay pin
    led.initialize();
    led.colorRed();
    Serial.begin(115200);  // serial monitor 
    
    wifly.initialize();
    wifly.setWlanConfig("mit", "MAK3-it-up"); //set ssid and passphrase
    
    pusher.setChannel("makeitup"); // name of pusher channel
    pusher.setKey("a4944fe864826d60193a"); // API key of Pusher application

    pusher.connect(); // open a websocket
    pusher.subscribe();
}

void loop() {
  if (blender) {
    digitalWrite(3, HIGH);
  }
  else {
    digitalWrite(3, LOW); //blender off
  }
  
  if (pusher.hasNextEvent()) { // check Pusher messages
    int value = pusher.getIntegerByName("value"); //look for a value named "value"
    if (value >= 0) {
      Serial.println("Event!");
      blender = !blender;
      led.colorOrange();
      delay(1000);
     }
  }   
  if (pusher.connected()) {
    led.colorGreen();
  }
  else {
    led.colorRed();
  }
}


/*
  GSM Based 4-Channel Light Control
  MCU: Arduino Uno/Nano
  GSM: SIM800L/SIM900
  Relays: 4 channels

  SMS Commands:
    LIGHT1 ON   -> Turn ON Light 1
    LIGHT1 OFF  -> Turn OFF Light 1
    LIGHT2 ON   -> ...
    LIGHT2 OFF
    LIGHT3 ON
    LIGHT3 OFF
    LIGHT4 ON
    LIGHT4 OFF
    ALL ON
    ALL OFF
*/

#include <SoftwareSerial.h>

SoftwareSerial gsm(7, 8); // RX, TX (Arduino RX=7, TX=8 -> Connect to GSM TX, RX)

// Relay pins
#define RELAY1 2
#define RELAY2 3
#define RELAY3 4
#define RELAY4 5

String smsContent = "";

void setup() {
  // Relay pins
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);

  // Default OFF
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
  digitalWrite(RELAY4, HIGH);

  Serial.begin(9600);
  gsm.begin(9600);

  Serial.println("GSM Light Control System");

  delay(1000);

  // GSM Init
  gsm.println("AT"); delay(500);
  gsm.println("AT+CMGF=1"); delay(500);      // SMS text mode
  gsm.println("AT+CNMI=1,2,0,0,0"); delay(500); // Auto show SMS
}

void loop() {
  if (gsm.available()) {
    char c = gsm.read();
    smsContent += c;

    // End of SMS content
    if (c == '\n') {
      smsContent.toUpperCase(); // make uppercase for matching
      Serial.println("SMS Received: " + smsContent);
      processSMS(smsContent);
      smsContent = ""; // clear buffer
    }
  }
}

void processSMS(String msg) {
  if (msg.indexOf("LIGHT1 ON") != -1) {
    digitalWrite(RELAY1, LOW);
    Serial.println("Light 1 ON");
  }
  else if (msg.indexOf("LIGHT1 OFF") != -1) {
    digitalWrite(RELAY1, HIGH);
    Serial.println("Light 1 OFF");
  }
  else if (msg.indexOf("LIGHT2 ON") != -1) {
    digitalWrite(RELAY2, LOW);
    Serial.println("Light 2 ON");
  }
  else if (msg.indexOf("LIGHT2 OFF") != -1) {
    digitalWrite(RELAY2, HIGH);
    Serial.println("Light 2 OFF");
  }
  else if (msg.indexOf("LIGHT3 ON") != -1) {
    digitalWrite(RELAY3, LOW);
    Serial.println("Light 3 ON");
  }
  else if (msg.indexOf("LIGHT3 OFF") != -1) {
    digitalWrite(RELAY3, HIGH);
    Serial.println("Light 3 OFF");
  }
  else if (msg.indexOf("LIGHT4 ON") != -1) {
    digitalWrite(RELAY4, LOW);
    Serial.println("Light 4 ON");
  }
  else if (msg.indexOf("LIGHT4 OFF") != -1) {
    digitalWrite(RELAY4, HIGH);
    Serial.println("Light 4 OFF");
  }
  else if (msg.indexOf("ALL ON") != -1) {
    digitalWrite(RELAY1, LOW);
    digitalWrite(RELAY2, LOW);
    digitalWrite(RELAY3, LOW);
    digitalWrite(RELAY4, LOW);
    Serial.println("All Lights ON");
  }
  else if (msg.indexOf("ALL OFF") != -1) {
    digitalWrite(RELAY1, HIGH);
    digitalWrite(RELAY2, HIGH);
    digitalWrite(RELAY3, HIGH);
    digitalWrite(RELAY4, HIGH);
    Serial.println("All Lights OFF");
  }
}

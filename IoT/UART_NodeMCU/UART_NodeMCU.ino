#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266HTTPClient.h>

const int bufferSize = 64;  // Adjust the size based on your requirement
char inputBuffer[bufferSize];

void setup() {
  Serial.begin(9600);  // Set the baud rate to match the Serial Monitor
}

void loop() {
  if (Serial.available() > 0) {
    // Read the incoming bytes until a newline character is encountered
    int bytesRead = Serial.readBytesUntil('\n', inputBuffer, bufferSize - 1);

    // Null-terminate the string
    inputBuffer[bytesRead] = '\0';

    // Print the received string to the Serial Monitor
    Serial.print("Received: ");
    Serial.println(inputBuffer);
  }
}

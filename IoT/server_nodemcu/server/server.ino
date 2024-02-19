#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266HTTPClient.h>


const char *ssid = "Sanket";
const char *password = "sanket@123";

const int bufferSize=64;
char inputBuffer[bufferSize];
char inputBuffer1[bufferSize];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial.flush();

  //WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
   }
  Serial.println("Serial Setup is completed");
  Serial.println("WiFi is connected");
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());

  //pinMode(A0, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available()>0){
    int bytesRead = Serial.readBytesUntil('\n',inputBuffer,bufferSize-1);
    inputBuffer[bytesRead]='\0';
    delay(1000);
     bytesRead = Serial.readBytesUntil('\n',inputBuffer1,bufferSize-1);
    inputBuffer1[bytesRead]='\0';
    Serial.print("Received1:");
    Serial.println(inputBuffer);
    Serial.print("\nReceived2 :");
     Serial.println(inputBuffer1);
 //float temp = atof(inputBuffer);
//ring body = String(temp);

 String body = "{ \"temperature\":"+String(inputBuffer)+",\"rain\":"+String(inputBuffer1)+" }";
 
    Serial.println(body);
  HTTPClient httpclient;
  WiFiClient wificlient;
  httpclient.begin(wificlient, "http://192.168.47.254:5000/monitor");
httpclient.addHeader("content-type", "application/json");
  int statuscode = httpclient.POST(body);
  Serial.printf("Status Code : %d\n", statuscode);
  delay(5000);
  }
}

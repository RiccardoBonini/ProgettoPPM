//#include "WiFi.h"



const char* ssid = "Cellai";
const char* password = "00000000";

const uint16_t port = 255;
const char * host = "192.168.43.209";


const int upsx = 2;
const int dwnsx = 4;
const int dwndx = 12;
const int updx = 13;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin ledPin as an output.
  pinMode(upsx, OUTPUT);
  pinMode(dwnsx, OUTPUT);
  pinMode(dwndx, OUTPUT);
  pinMode(updx, OUTPUT);

  Serial.begin(115200);

  //WiFi.begin(ssid, password);
  //while (WiFi.status() != WL_CONNECTED) {
    //delay(500);
    //Serial.println("...");
  //}
  //Serial.print("WiFi connected with IP: ");
  //Serial.println(WiFi.localIP());
}

// the loop function runs over and over again forever
void loop() {
  //WiFiClient client;
  
  //if (!client.connect(host, port)) {

   //Serial.println("Connection to host failed");

   //delay(1000);
   //return;
  //}
   //Serial.println("Connected to server successful!");


   //char c = client.read();
   //Serial.print(c);


  digitalWrite(updx, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(upsx, HIGH);
  digitalWrite(dwnsx, LOW);
  digitalWrite(dwndx, LOW);
//  delay(1000);                  // wait for a second
//  digitalWrite(updx, LOW);    // turn the LED off by making the voltage LOW
//  delay(1000);                  // wait for a second
}

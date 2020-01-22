#include <Bridge.h>
#include <YunClient.h>
#include <ArduinoJson.h>
#define PORT 255

#define asseX A5 
#define asseY A4 
#define PressPin 7

#define O0 11
#define O1 10
#define O2 9
#define O3 6
#define O4 5
#define O5 3
#define I0 A0
#define I1 A1
#define I2 A2
#define I3 A3

// These constants won't change. They're used to give names
// to the pins used:
const int analogInPin1 = I0; // Analog input pin that the Accelerometer'sfirst pin is attached to

const int analogInPin2 = I1; // Analog input pin that the Accelerometer'ssecond pin is attached to

const int analogOutPin1= O0; // Analog output pin that the LED is attachedto

const int analogOutPin2= O1; // Analog output pin that the LED is attachedto

int sensorValue1 = 0; // value read from the Accelerometer's first pin

int sensorValue2 = 0; // value read from the Accelerometer's second pin

int outputValue1 = 0; // value output to the PWM (analog out)

int outputValue2 = 0; // value output to the PWM (analog out)


// Define our client object
YunClient client;
bool Connected;

// Make the client connect to the desired server and port
IPAddress addr(192, 168, 43, 209);
  
// Or define it using a single unsigned 32 bit value
// IPAddress addr(0xc0a8sab9); // same as 192.168.42.185
  
// Or define it using a byte array
// const uint8 addrBytes = {192, 168, 42, 185};
// IPAddress addr(addrBytes);

// Or connect by a server name and port.
// Note that the Yun doesn't support mDNS by default, so "Yun.local" won't work
// client.connect("ServerName.com", PORT);

DynamicJsonDocument  doc(200);

void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  // Bridge startup
  Bridge.begin();

  doc["X"] = 0;
  doc["Y"] = 0;
  //doc["B"] = false;
  
  Serial.begin(115200);
  Serial.println("Client connecting on port 255");
  Connected = false;
}

void loop()
{
  // Is a connection currently active?
  if (!Connected)
  {
    // Not currently connected, try to establish a connection
    client.connect(addr, PORT);
    if (client.connected())
    {
      Serial.println("Connected to the server.");

      // Send something to the client
      client.println("Hello Server!");
      
      // Remember that there is a connection
      Connected = true;
    }
    else
    {
      // The connection attempt has failed.
      Serial.println("Could not connect to the server.");  
    
      // Give some time before trying again.
      // A real program needs to be more inteligent here.
      delay(5000);
    }
  }
  
  // Is a connection currently active?
  // Not an ELSE clause from the above IF, because a
  // new connection might have just been established.
  if (Connected)
  {
    // We think we are connected. Is that true?
    if (client.connected())
    {
      // Yes, we really are connected.
      // Send something to the client
     

      int xVal, yVal;
     
   
      xVal = analogRead (analogInPin1);
      yVal = analogRead (analogInPin2);
      //buttonVal = digitalRead (PressPin);

      //JsonArray coordinates = doc.createNestedArray("XY");
      doc["X"] = xVal;
      doc["Y"] = yVal;
      //doc["B"]= buttonVal;
      serializeJson(doc, Serial);
      Serial.print("");
      serializeJson(doc, client);

      //JsonArray pressButton = doc.createNestedArray("B");
      
      
      
      // Delay just to prevent too much data streaming
      // to the server, a real application will need to
      // be more intelligent here.
      //delay(1000);
      
      // Read all incoming bytes available from the server and print them
      while (client.available())
      {
        char c = client.read();
        Serial.print(c);
      }
      Serial.flush();
    }
    else
    {
       // We think we are connected, but we aren't.
       // The connection must've just closed on us.
       Serial.println("Server connection closed!");
      
       // Clean up the client connection
       client.stop();
      
       // Track that we are no longer connected.
       // This will try to establish a connection the next time around.
       Connected = false;
    }
  }
}

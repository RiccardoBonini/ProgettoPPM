#include <Bridge.h>
//#include <YunServer.h>
#include <YunClient.h>
#include <ArduinoJson.h>
#define PORT 255
IPAddress addr(192, 168, 43, 209);

#define asseX A5 
#define asseY A4 
#define PressPin 7

//YunServer server(PORT);
YunClient client;

static boolean clientActive = false;

DynamicJsonDocument  doc(200);

#include "NAxisMotion.h"
#include <Wire.h>

NAxisMotion mySensor;
unsigned long lastStreamTime = 0;
const int streamPeriod = 20;          //To stream at 50Hz without using additional timers (time period(ms) =1000/frequency(Hz))
bool updateSensorData = true;         //Flag to update the sensor data. Default is true to perform the first read before the first stream

void setup() {
  
  //Peripheral Initialization
  Serial.begin(115200);           //Initialize the Serial Port to view information on the Serial Monitor
  I2C.begin();                    //Initialize I2C communication to the let the library communicate with the sensor.

  //Sensor Initialization
  mySensor.initSensor();          //The I2C Address can be changed here inside this function in the library
  mySensor.setOperationMode(OPERATION_MODE_NDOF);   //Can be configured to other operation modes as desired
  mySensor.setUpdateMode(MANUAL);  //The default is AUTO. Changing to MANUAL requires calling the relevant update functions prior to calling the read functions
  //Setting to MANUAL requires fewer reads to the sensor
  Bridge.begin();
  /*server.noListenOnLocalhost();
  server.begin();
  client = server.accept();*/
  
  
  //JsonObject root = jsonBuffer.createObject();
  doc["X"] = 0;
  doc["Y"] = 0;
  doc["Z"] = 0;
  
}

void loop() {
  if (updateSensorData)  //Keep the updating of data as a separate task
  {
    mySensor.updateEuler();
    mySensor.updateLinearAccel();
    mySensor.updateMag();
    mySensor.updateGyro();
    mySensor.updateCalibStatus();  //Update the Calibration Status
    updateSensorData = false;
  }
  client.connect(addr, PORT);
  if(client.connected()){
    if ((millis() - lastStreamTime) >= streamPeriod)
  
  {
    lastStreamTime = millis();

    

    //Acceleration

    //Serial.print(" AccelX: ");
    doc["X"]= mySensor.readLinearAccelX();
    Serial.print(", ");

    //Serial.print(" AccelY: ");
    doc["X"]= mySensor.readLinearAccelY();
    Serial.print(", ");

    //Serial.print(" AccelZ: ");
    doc["X"]= mySensor.readLinearAccelZ();
    Serial.print(", ");

    

    serializeJson(doc, Serial);
    serializeJson(doc, client);


    updateSensorData = true;
    }
  }
  /*else{
    if (clientActive){
      client.stop();
      Serial.println("Client disconnected.");
      }
      clientActive = false;
      client = server.accept();
   }*/
   else {
if (clientActive) {
client.stop();       // Disconnected from the server
Serial.println("Client disconnected.");
}}
   delay(300);
}

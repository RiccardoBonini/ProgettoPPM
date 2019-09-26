#define asseX A5 
#define asseY A4 
#define PressPin 7

void setup ()
{
  Serial.begin (9600); 
  pinMode (PressPin, INPUT_PULLUP);
}
void loop ()
{
 int xVal, yVal;
 bool buttonVal;
 
 xVal = analogRead (asseX);
 yVal = analogRead (asseY);
 buttonVal = digitalRead (PressPin);
 Serial.print("X = ");
 Serial.println (xVal, DEC);
 Serial.print ("Y = ");
 Serial.println (yVal, DEC);
 Serial.print("Button is ");
 if (buttonVal == LOW) Serial.println ("PRESS");
 else Serial.println ("Not Press");
 delay (500);
}

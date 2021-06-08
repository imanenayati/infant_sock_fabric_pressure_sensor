/*
Pressure Sensitive Garment Sensor

Iman H. Enayati
Department of Orthopedic Surgery
University of California, Los Angeles
imanhenayati@ucla.edu

Author's Notes: The following project records value from a fabric pressure sensor
positioned in the heal area of an infant's sock. The pressure sensor readings are
evaluated and a RBG LED signals a threshold value has been reached. The LED emits
a constant red color until the threshold value is met, whereby the LED turns off,
indicating threshold pressure has been successfully met. The following code does
not support low-energy bluetooth functionality. Contact author for inquiries and
support.

Last Updated: June 1, 2021
*/

#define PIN 5 //Define pin for neopixels

#define NUMPIXELS 1 //number of pixels that will be used

#include <Filters.h>

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Defining Variables
int delayval = 15;            // delay for .15 sec
const int analogInPin1 = 10;  //pressure fabric for OUTSIDE, PIXEL 1
int sensorHeelValue = 0;      //value from heel pressure sensor
int sensorInsideValue = 0;    //value from inside pressure sensor
int sensorOutValue = 0;       //value from outside pressure sensor
int FilteredSensorHeelValue = 0;
int FilteredSensorInsideValue = 0;
int FilteredSensorOutValue = 0;

void setup() {

  Serial.begin(9600);
  
  pixels.begin();             // This initializes the NeoPixel library.
  Serial.begin(9600);
  pixels.setBrightness(255);
  
  pinMode(10, INPUT_PULLUP); //sensor pin

  pinMode(5, OUTPUT);        //LED pin
  pixels.show();

//startup light sequence
for (int i = 0; i <= 255; i++){
    pixels.setPixelColor(0, pixels.Color(i,i,i));
    pixels.show();
    delay(20);
  }
 delay(80);


}

void loop() {

  // read the analog in values from digital pin:
  sensorOutValue = analogRead(analogInPin1);

  //Set up for LowPass filter
  FilterOnePole lowpassFilter(LOWPASS,50);

  //Filter Heel sensor signal value due to high noise levels
  lowpassFilter.input(sensorHeelValue);

  //Create new variable to hold filtered signal
  FilteredSensorHeelValue = lowpassFilter.output();
             
  //Print results to serial monitor:
  Serial.print("sensor values = " );                       
  Serial.print(sensorOutValue);

  
/*If the sensor value is above a provided threshold (indicating inadequate pressure), 
turn on the corresponding neopixel RED. If sensor value is not below threshold, turn 
corresponding neopixel off*/

if (sensorOutValue >= 60) {
    pixels.setPixelColor(0, pixels.Color(255,0,0));
    pixels.show();
    Serial.println("NOT TRIGGERED");
    delay(delayval);
  }
else{
    pixels.setPixelColor(0, pixels.Color(0,0,0));
    pixels.show();
    Serial.println("TRIGGERED");
    delay(delayval);
  }


}

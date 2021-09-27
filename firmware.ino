/*
Pressure Sensitive Garment Sensor

Iman H. Enayati
Department of Orthopedic Surgery
University of California, Los Angeles
imanhenayati@ucla.edu

Author's Notes: The following project records values from an infant's sock embedded with
a fabric pressure sensor positioned below the calcaneus. The pressure sensor readings are
evaluated and a RBG LED signals a threshold value has been reached. The LED emits a 
constant red color until the threshold value is met, whereby the LED turns off,
indicating threshold pressure has been successfully met. The following code does not 
support low-energy bluetooth functionality. Contact author for inquiries and support.

Last Updated: June 1, 2021
*/

  #include <Filters.h>
  
  int sensorOutValue = 0;       //value from outside pressure sensor
  int FilteredSensorOutValue = 0;
  
void setup() {
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize analog pin A0 as sensor input
  pinMode(A0, INPUT_PULLUP);

  // setup serial communication
  Serial.begin(9600);
}


void loop() {


  // read the analog in values from digital pin:
  sensorOutValue = analogRead(A0);

  //Set up for LowPass filter
  FilterOnePole lowpassFilter(LOWPASS,50);

  //Filter Heel sensor signal value due to high noise levels
  lowpassFilter.input(sensorOutValue);

  //Create new variable to hold filtered signal
  FilteredSensorOutValue = lowpassFilter.output();

  //Serial.println("Sensor value = " );
  Serial.println(FilteredSensorOutValue);  

  delay(10);
}

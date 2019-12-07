/*
 DC Motor Control 

 This program drives a brush and brushless DC motor.
 The motor is attached to digital pins 3 and 9 of the Arduino.

 The motor spins at Full rotation speed for 2 seconds,
 then half the rotation speed for 2 seocnds,
 and then no movement from motor for 2 seconds. 

 Created November 7, 2019
 by Tyler Adam Martinez 

 */
  int full = HIGH;
  int half = 255/2;
  int off = LOW;
 
void setup() {
  // ALL the pins are PWM 
  pinMode(3, OUTPUT); // VCC loop 
  pinMode(9, OUTPUT); //GND loop

  // Serial 
  Serial.begin(9600);
}

void loop() {
  //Full speed CW loop
  digitalWrite(3, full);
  digitalWrite(9, off);
  Serial.println("full speed");
  delay(2000); //2 seconds 
  
  //Half speed CW loop 
  analogWrite(3, half);
  analogWrite(9, off);
  Serial.println("half speed");
  delay(2000);
  
  //off 
  digitalWrite(3, off);
  digitalWrite(3, off);
  Serial.println("motor off"); 
  delay(2000);
  

}

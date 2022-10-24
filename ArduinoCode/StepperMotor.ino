/*
 Stepper Motor Control 

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor spins at Full rotation speed for 2 seconds,
 then half the rotation speed for 2 seocnds,
 and then no movement from motor for 2 seconds. 

 Created November 7, 2019
 by Tyler Adam Martinez 

 */

#include <Stepper.h>
unsigned int full = 60;
unsigned int half = 30;
unsigned int off = 0;
const int stepsPerRevolution = 32;  //number of steps per revolution
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11); // initialize the stepper library on pins 8 through 11 

void setup() {
  Serial.begin(9600); // initialize the serial port
}

void loop() {
  // step one revolution in one direction and will be at full speed
  myStepper.setSpeed(full);  // set the speed at 60 rpm or full speed
  Serial.println("clockwise: FULL SPEED"); //print to Serial monitor 
  myStepper.step(64); //Detakes the direction of the stepper motor
  delay(2000); //delay function is in miliseconds 

  //step one revolution in one direction and will be at half speed
  myStepper.setSpeed(half); // set the speed at 30 rpm or half speed 
  Serial.println("clockwise: HALF SPEED"); //print to Serial monitor 
  myStepper.step(32); //Detakes the direction of the stepper motor
  delay(2000); //delay function is in miliseconds 

  //Stop the revolution of the motor 
  myStepper.setSpeed(off); // set the speed at 0 rpm or off 
  Serial.println("no movement"); //print to Serial monitor 
  myStepper.step(0); //Detakes the direction of the stepper motor
  delay(2000); //delay function is in miliseconds 

}

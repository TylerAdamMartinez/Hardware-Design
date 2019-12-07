/*
 Servo Motor Control 

 This program controls a servo motor.
 The servo motor is attached to digital(PWM) pin 9 of the Arduino.
 The power and ground for the motor comes from Ardunino 5V and GND pins.  

 The motor rotates from 0 degress to 180 degress,
 then motor rotates from 180 degress to 0 degress,
 and then no movement from motor for 1 second. 

 Created November 15, 2019
 by Tyler Adam Martinez 

 */
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

unsigned int pos = 0;    // variable to store the servo position

void setup() 
{
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
 
  Serial.begin(9600);  //Serial Communication
}

void loop() 
{

  // goes from 0 degrees to 180 degrees
  for (pos = 0; pos <= 180; pos += 1) // in steps of 1 degree
  { 
    myservo.write(pos);              // tell servo to go to position in variable 'positive'
    Serial.println("0 to 180");
    delay(10);                       // waits 10ms for the servo to reach the position
  }

  // goes from 180 degrees to 0 degrees
  for (pos = 180; pos >= 0; pos -= 1) 
  { 
    myservo.write(pos);
    Serial.println("180 to 0");
    delay(10);                       
  }

  //This will stop movement of the motor for the one second.
    Serial.println("No Movement");
    delay(1000);

}

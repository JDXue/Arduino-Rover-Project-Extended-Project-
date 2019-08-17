/******Adafruit motor shield testing********/
//inspired by https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();


Adafruit_DCMotor *M1 = AFMS.getMotor(1);
Adafruit_DCMotor *M2 = AFMS.getMotor(2);
Adafruit_DCMotor *M3 = AFMS.getMotor(3);
Adafruit_DCMotor *M4 = AFMS.getMotor(4);


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  // Set the speed to start, from 0 (off) to 255 (max speed)
  M1->setSpeed(150);
  M1->run(FORWARD);
  M2->setSpeed(150);
  M2->run(FORWARD);
  // turn on motor
  M1->run(RELEASE);
  M2->run(RELEASE);

  M3->setSpeed(150);
  M3->run(FORWARD);
  M4->setSpeed(150);
  M4->run(FORWARD);
  // turn on motor
  M3->run(RELEASE);
  M4->run(RELEASE);
  
}

void loop() {
  int i;

  Serial.println("Motor 1 forwards");

  M1->run(FORWARD);
  for (i = 0; i < 255; i++) {
    M1->setSpeed(i);
    delay(10);
  }
  for (i = 255; i != 0; i--) {
    M1->setSpeed(i);
    delay(10);
  }
  M1->run(RELEASE);

  Serial.println("Motor 2 forwards");

  M2->run(FORWARD);
  for (i = 0; i < 255; i++) {
    M2->setSpeed(i);
    delay(10);
  }
  for (i = 255; i != 0; i--) {
    M2->setSpeed(i);
    delay(10);
  }
  M2->run(RELEASE);

  Serial.println("Motor 1 and 2, full speed");
  M1->run(FORWARD);
  M1->setSpeed(255);
  M2->run(FORWARD);
  M2->setSpeed(255);
  delay(3000);
  M1->run(RELEASE);
  M2->run(RELEASE);

  delay(1000);

 Serial.println("Motor 3 forwards");

  M3->run(FORWARD);
  for (i = 0; i < 255; i++) {
    M3->setSpeed(i);
    delay(10);
  }
  for (i = 255; i != 0; i--) {
    M3->setSpeed(i);
    delay(10);
  }
  M3->run(RELEASE);

  Serial.println("Motor 4 forwards");

  M4->run(FORWARD);
  for (i = 0; i < 255; i++) {
    M4->setSpeed(i);
    delay(10);
  }
  for (i = 255; i != 0; i--) {
    M4->setSpeed(i);
    delay(10);
  }
  M4->run(RELEASE);

  Serial.println("Motor 3 and 4, full speed");
  M3->run(FORWARD);
  M3->setSpeed(255);
  M4->run(FORWARD);
  M4->setSpeed(255);
  delay(3000);
  M3->run(RELEASE);
  M4->run(RELEASE);

  Serial.println("All motors, full speed");
  M3->run(FORWARD);
  M3->setSpeed(255);
  
  M4->run(FORWARD);
  M4->setSpeed(255);
  
  M1->run(FORWARD);
  M1->setSpeed(255);
  
  M2->run(FORWARD);
  M2->setSpeed(255);
  
  delay(3000);
  M3->run(RELEASE);
  M4->run(RELEASE);
  M1->run(RELEASE);
  M2->run(RELEASE);
   
  delay(1000); 

}

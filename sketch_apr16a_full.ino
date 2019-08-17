/*****Programmed algorithm for EPQ rover bot********/
//LED to light up when rover goees into reaction subroutine
const int led = 8;

//-----------Motor----------------
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// create motor shield object
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *M1 = AFMS.getMotor(1);
Adafruit_DCMotor *M2 = AFMS.getMotor(2);
Adafruit_DCMotor *M3 = AFMS.getMotor(3);
Adafruit_DCMotor *M4 = AFMS.getMotor(4);

//-------Vibration Sensors----------
int vib1;
int vib2;

//-------State Subroutines------------
boolean react(int r1,int r2) {
  boolean go_protect = false;
  int i;
  int thresh2 = 350;


  int retract = 255; //sets speed of motors that move antennae

  digitalWrite(led,HIGH);
  
  if ((r1 < thresh2) && (r2 < thresh2)) {
    go_protect = true;

    //full reaction occurs
    Serial.println("Full reaction in both antennae");
    M3->setSpeed(retract);
    M3->run(FORWARD);
    M4->setSpeed(retract);
    M4->run(FORWARD);
    delay(1000);
    M3->run(RELEASE);
    M4->run(RELEASE);
  }
  else if ((r1 < thresh2) || (r2 < thresh2)) {
    go_protect = false;

    //full reaction occurs in one antennae
    if (r1 > r2) {
      Serial.println("Full reaction in one antennae");
      M3->setSpeed(retract);
      M3->run(FORWARD);
      delay(retract);
      M3->run(RELEASE);
    }
    else if (r1 < r2){
      M4->setSpeed(retract);
      M4->run(FORWARD);
      delay(1000);
      M4->run(RELEASE);
    }
    else {
      go_protect = false;
      // if vibrations are not severe enough to reach second threshold, only half reaction occurs
      M3->setSpeed(retract);
      M3->run(FORWARD);
      M4->setSpeed(retract);
      M4->run(FORWARD);
      delay(500);
      M3->run(RELEASE);
      M4->run(RELEASE);
    }
  }
    digitalWrite(led,LOW);
    return go_protect;
  }

void turns(int read1, int read2) {
    int i;

    //antennae needs to move out before rover begins to turn   
    if (read1 > read2) {
      Serial.println("Antennae moving out");
       M3->run(BACKWARD);
        for (i = 0; i < 255; i++) {
          M3->setSpeed(i);
          delay(5);
        }
        delay(1000);
      M3->run(RELEASE);

      Serial.println("Turning left");
      M1->setSpeed(150);
      M1->run(FORWARD);
      M2->setSpeed(150);
      M2->run(BACKWARD);
      delay(3000);
      M1->run(RELEASE);
      M2->run(RELEASE);
    }
    else{
      Serial.println("Antennae moving out");
      M4->run(BACKWARD);
        for (i = 0; i < 100; i++) {
          M4->setSpeed(i);
          delay(5); 
        }
      M4->run(RELEASE);
      
      Serial.println("Turning right");
      M1->setSpeed(150);
      M1->run(BACKWARD);
      M2->setSpeed(150);
      M2->run(FORWARD);
      delay(3000);
      M1->run(RELEASE);
      M2->run(RELEASE);
    }

  }

void protect(){
    int thresh3 = 300;
    Serial.println("Protect!");
    
    //wait 2 secs
    delay(2000);
    int newread1 = analogRead(A0);
    delay(500);
    int newread2 = analogRead(A1);
    
    //decides whether to continue protecting 
    while ((newread1 < thresh3)||(newread2 < thresh3)){
      delay(1000);
      // takes a new reading every second
      newread1 = analogRead(A0);
      delay(500);
      newread2 = analogRead(A1);
      Serial.print("Sensor A: ");
      Serial.print(newread1);
      Serial.print("Sensor B: ");
      Serial.println(newread2);
      Serial.println("Protect!");
    }

    //turns(newread1, newread2);
  }


//intial subroutine, only runs once
void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Rover is waking up");
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  //speed variables for motors
  int slow = 100;
  int pace = 200;

  // Set the speed to start, from 0 (off) to 255 (max speed)
  M1->setSpeed(slow);
  M2->setSpeed(slow);
  M3->setSpeed(255);
  M4->setSpeed(255);

  M3->run(FORWARD);
  M4->run(FORWARD);
  delay(1000);
  // turn on motor
  M3->run(RELEASE);
  M4->run(RELEASE);

  // rover begins moving forward
  M1->run(FORWARD);
  M2->run(FORWARD);
  
  int i;
  for (i = 0; i < slow; i++) {
    M1->setSpeed(i);
    M2->setSpeed(i);
    delay(10);
  }
  pinMode(led,OUTPUT);
}

//subroutine continues to run
void loop() {
  // limit that seperates casual vibrations from vibrations
  // that could imply danger
  // intial threshold for vibrations
  /**lower values from the vibrations sensors imply greater vibrations
  because the spring inside the switch closes the current, causing a drop in voltage in the circuit **/
  int threshold = 300;
  int read1 = 0;
  int read2 = 0;
  int i;
  //speed variables for motors
  int slow = 100;
  int pace = 200;

  //rover is moving forward
  M1->run(FORWARD);
  M2->run(FORWARD);

  M3->run(RELEASE);
  M4->run(RELEASE);
  
  // first reading taken from vibration sensors
  read1 = analogRead(A0);
  //needs a gap between readings to get a more accurate reading from both analog pins
  delay(500); 
  read2 = analogRead(A1);

  Serial.print("Sensor A: ");
  Serial.print(read1);
  Serial.print("Sensor B: ");
  Serial.println(read2);
  
  
  if ((read1 < threshold) || (read2 < threshold)) {
    // rover stops moving
    M1->run(RELEASE);
    M2->run(RELEASE);

    //writing to serial output is useful for debugging, understanding "thought process" of rover
    // as it calls different subroutines
    Serial.println("Potential danger detected!");
    // calls reaction function
    boolean hide = react(read1,read2);
    //if react returns true, call protect procedure
    //hide allows potential danger be evaluated by the react subroutine
    if (hide == true) {
      Serial.println("Danger detected! Protect.");
      protect();
      //antennae move out again
      M3->run(BACKWARD);
      M4->run(BACKWARD);
        for (i = 0; i < 255; i++) {
          M3->setSpeed(i);
          M4->setSpeed(i);
          delay(5);
        delay(1000);  
        }
        
      // rover begins moving forward again
      M1->run(FORWARD);
      M2->run(FORWARD);
      for (i = 0; i < slow; i++) {
        M1->setSpeed(i);
        M2->setSpeed(i);
        delay(10);
      }
    }
    else if (hide == false) {
      Serial.println("Danger not threatening, turning rover.");
      turns(read1,read2);


      //begins moving forwards again
      M1->run(FORWARD); 
      M2->run(FORWARD);
      for (i = 0; i < slow; i++) {
        M1->setSpeed(i);
        M2->setSpeed(i);
        delay(10);
       
       }
      
    }

    delay(1000);
  }
  else {
    Serial.println("No danger detected so far.");
  }
  delay(1000);
}

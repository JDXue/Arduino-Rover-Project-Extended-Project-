/* Vibration Sensor (Shake Switch) 
   Dev: Michalis Vasilakis - Date: 9/9/2015 - www.ardumotive.com       */
   

// I have modified the code here to use with a LED, since a buzzer
// is too irritating when testing
const int led = 8; 
int sensor1;//Variable to store analog value (0-1023)
int sensor2;

void setup()
{
  Serial.begin(9600);      //Only for debugging
  pinMode(led, OUTPUT);
}

int readValue(int pin){
  analogRead(pin);
  int value = analogRead(pin);
  return value;
}

void loop()
{
  sensor1 = readValue(0);
  delay(500);
  sensor2 = readValue(1);
  //While sensor is not moving, analog pin receive 1023~1024 value
  
  // I have found when using a 100 ohm resistor, using a threshold of 400
  // prevents the sensor from being too sensitive to smaller vibrations
 //using the serial plotter I have found that the pin recieves higher than 
 //500 if a vibration occurs, therefore I should be looking for an outliers
 // from a range 300<x<500
  if ((sensor1<300)||(sensor1>500)||(sensor2<300)||(sensor2>500)){
    digitalWrite(led,HIGH);
    delay(1000);
    digitalWrite(led,LOW);
    Serial.print("Sensor A: ");
    Serial.print(sensor1);
    Serial.print("Sensor B: ");
    Serial.println(sensor2);
  }
  
  else{ 
    digitalWrite(led,LOW);
    Serial.print("Sensor A: ");
    Serial.print(sensor1);
    Serial.print("Sensor B: ");
    Serial.println(sensor2);
  }
  
  
}

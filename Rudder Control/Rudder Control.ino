#include <Servo.h>

const byte servoPin = 9; // Signal pin for the servo.
const byte potentiometerPin = A0; // analog input pin for the potentiometer.
Servo servo; // Declaring an instance of the servo class as an object
int analogVal; // Declaring a int to store the analog values from the potentiometer

void setup() {
  servo.attach(servoPin); // Assigning the pin to the servo object to initiate control
}

void loop() {
  analogVal = analogRead(potentiometerPin); // To read the values from the potentiometer
  analogVal = map(analogVal, 0, 1023, 0, 180);  // Mapping the direction of the analog values (from 0 - 1023 to 0 - 180)
  servo.write(analogVal); // Sends the mapped value to servo
  delay(15); //Delays loop by 15ms
}

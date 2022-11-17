// Define Input Connections
#define CH1 3 //ailerons
#define CH2 5 //elevators
#define CH3 6 //throttle
#define CH4 9 //rudder
#define CH5 10 //open channel we can use for other stuff
#define CH6 11 //SWA switch

//output pins
#define THROTTLE 2
#define AILERONS 4
#define ELEVATORS 7
#define RUDDER 8

//including servo library and creating four objects of the class, one for each servo we need to control
#include<Servo.h>
Servo throttle;
Servo ailerons;
Servo elevators;
Servo rudder;

// Integers to represent values from sticks and pots
int ch1Value;
int ch2Value;
int ch3Value;
int ch4Value; 
int ch5Value;

//ints for pwm values to be written to servos
int pwm1;
int pwm2;
int pwm3;
int pwm4;


// Boolean to represent switch value
bool ch6Value;

// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

// Read the switch channel and return a boolean value
bool readSwitch(int channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}

void setup(){
  // Set up serial monitor
  Serial.begin(115200);
  
  // Set all pins as inputs
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  pinMode(CH5, INPUT);
  pinMode(CH6, INPUT);

  //setting servo pins as outputs
  pinMode(THROTTLE, OUTPUT);
  pinMode(AILERONS, OUTPUT);
  pinMode(ELEVATORS, OUTPUT);
  pinMode(RUDDER, OUTPUT);

//attaching the pin of each servo to its respective object in the program
throttle.attach(THROTTLE);
ailerons.attach(AILERONS);
elevators.attach(ELEVATORS);
rudder.attach(RUDDER);
throttle.writeMicroseconds(1500); // send "stop" signal to ESC. Also necessary to arm the ESC.

delay(7000); // delay to allow the ESC to recognize the stopped signal.
}


void loop() {
  
  // Get values for each channel
  ch1Value = readChannel(CH1, -100, 100, 0);
  ch2Value = readChannel(CH2, -100, 100, 0);
  ch3Value = readChannel(CH3, -100, 100, -100);
  ch4Value = readChannel(CH4, -100, 100, 0);
  ch5Value = readChannel(CH5, -100, 100, 0);
  ch6Value = readSwitch(CH6, false); //ch6Value is a bool that we can use to toggle stuff later
  
  // Mapping and writing values
  //Note that the receiver returns values from -100,100; but the ESC wants values 1100,1900; and the servos want values 0,180; so we must map the values before we write

  
  pwm3=map(ch3Value,-100,100,1100,1900);
  throttle.writeMicroseconds(pwm3);

  pwm1=map(ch1Value, -100,100,0,180);
  ailerons.write(pwm1);

  pwm2=map(ch2Value, -100, 100, 0, 180);
  elevators.write(pwm2);

  pwm4=map(ch4Value, -100, 100, 0, 180);
  rudder.write(pwm4);

  Serial.print(pwm3);
  Serial.print(" ");
  Serial.print(pwm1);
  Serial.print(" ");
  Serial.print(pwm2);
  Serial.print(" ");
  Serial.print(pwm4);
  Serial.println(" ");
  delay(15);
}

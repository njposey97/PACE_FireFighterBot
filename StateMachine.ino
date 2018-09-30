/*
* Thank you to the creator of this code used to control the HC-SR04 Range Sensor.
* We have adjusted the program to suit our needs, but main credit goes to the creator below!
* 
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
/


//HC SR04 
const int echoPin = 8;
const int trigPin = 9;

//Button used for testing of ISR
const int button = 7;

long duration;
int distance;

void buttonPress(){
  //To be written at next meeting
  }

void setup() {
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  
  //Interrupt to be used when testing ISR
  attachInterrupt(digitalPinToInterrupt(2), buttonPress, RISING);

  //Used in order to read measurements from the HC-SR04
  Serial.begin(9600);
}

void URSense() {
// Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

// Calculating the distance
  distance= duration0.034/2;
  //distance in inches becasue we are stoopid murcan' hoo don kno metric sistem
  distance *= 0.393701;

  Serial.print("Distance: ");
  Serial.println(distance);

  //Delay will be removed in final code, but is kept in the meantime for testing
  delay(1000);
}

//This is where the State Machine we have designed will be programmed
void loop(){
  URSense();
  }

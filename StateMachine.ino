int echoPin[3] = {10,7,4};
int trigPin[3] = {11,6,3};

long duration[3];
int distance[3] = {};

//If needed for communication, we can create a struct called package which will contain all data
/*
struct Package{
  int prevLoc;
  int curLoc;
  int distanceNeeded = 0;
  int direction;
}
*/

//Values used and updated to determine robot movement
//Assuming sensor 0 is on left, and 2 is on right
int  prevLoc;
int curLoc;
int distanceNeeded = 0;
//Direction is 0 if not moved, -1 if moving left, 1 if moving right
int direction;

void setup() {  

  //Initialize pins
  for(int i = 0; i < 3; i++){
    pinMode(echoPin[i], INPUT);
    pinMode(trigPin[i], OUTPUT);
  }
  
  Serial.begin(9600);
}


void URSense() {
 Serial.print("HI1\t");
  //loops once for each sensor
  for(int i = 0; i < (sizeof(echoPin)); i++){
    // Clears the trigPin
    digitalWrite(trigPin[i], LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin[i], LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration[i] = pulseIn(echoPin[i], HIGH);
    // Calculating the distance
    distance[i] = (duration[i]*0.034)/2;
        
    //Trash values which can't be possible
    //        0 < distance < 154 cm
    if(distance[i] <= 0 || distance[i] >= 154){
      distance[i] = -1;
    }
  }
  //Set values for curLoc, distanceNeeded, and direction
  //Error with sensors, try again
  if((distance[0] == -1) && (distance[1] == -1) && (distance[2] == -1))
    URSense();
   
   //Set new values for curloc and distanceNeeded 
    if((distance[0] < distance[1]) && (distance[0] != -1) && (distance[0] < distance[2])){
      curloc = 0;
      distanceNeeded = distance[0];
    }
    else if((distance[1] < distance[0]) && (distance[1] != -1) && (distance[1] < distance[2])){
      curloc = 1;
      distanceNeeded = distance[1];
    }
    else if((distance[2] < distance[1]) && (distance[2] != -1) && (distance[2] < distance[0])){
      curloc = 2;
      distanceNeeded = distance[2];
    }
    else{
      //No value is valid, so must retake measurements
      URSense();
    }
    
  //Update location info
  prevLoc = curLoc;

  //Direction is 0 if not moved, -1 if moving left, 1 if moving right
  direction = curLoc - prevLoc;

  //Delay used in order to prevent issues with timing
  //Value to be adjusted depending on needs
  delay(50);
}

//void  sendData(){
  //This is where we will send data to the main board after being given an interrupt
  //This will most likely be accomplished using IC2 protocol with this board as the slave
//}

void loop(){
  
  URSense();
  Serial.print("HI4\t");
  Serial.print("Direction: ");
  Serial.println(direction);
  Serial.print("Distance: ");
  Serial.println(distanceNeeded);
  Serial.print("\n\n");
  }

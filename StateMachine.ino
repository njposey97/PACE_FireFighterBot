int echoPin[3] = {x,y,z};
int trigPin[3] = {x,y,z};

long duration[3];
int distance[3] = {};

//Values used and updated to determine robot movement
//Assuming sensor 0 is on left, and 2 is on right
int	prevLoc;
int	curLoc;
int	distanceNeeded;
//Direction is 0 if not moved, -1 if moving left, 1 if moving right
int	direction;

void setup() {
	for(int i = 0; i < (sizeof(echoPin)); i++){
		pinMode(echoPin[i], INPUT);
		pinMode(trigPin[i], OUTPUT);
	}
	
  //Interrupt to be used when testing ISR
  attachInterrupt(digitalPinToInterrupt(w), sendData, RISING);

}
void URSense() {
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
		//   			0 < distance < 154 cm
		if(distance[i] <= 0 || distance[i] >= 154){
			distance[i] = -1;
		}
	}
	//Set values for curLoc, distanceNeeded, and direction
	
	//Error with sensors, try again
	if((distance[0] == -1) && (distance[1] == -1) && (distance[2] == -1))
		break;
		
	//Update location info
	prevLoc = curLoc;
	
	//Assuming only one sensor picks up values, may change during testing
	else if(distance[0] != -1){
		curLoc = 0;
		distanceNeeded = distance[0];
		}
	else if(distance[1] != -1){
		curLoc = 1;
		distanceNeeded = distance[1];
		}
	else if(distance[2] != -1){
		curLoc = 2;
		distanceNeeded = distance[2];
		}
		
	//Direction is 0 if not moved, -1 if moving left, 1 if moving right
	direction = curLoc - prevLoc;
	
  //Delay used in order to prevent issues with timing
  //Value to be adjusted depending on needs
  delay(50);
}

void	sendData(){
  //This is where we will send data to the main board after being given an interrupt
  //This will most likely be accomplished using IC2 protocol with this board as the slave
}


void loop(){
  URSense();
  }

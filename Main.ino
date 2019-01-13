// ARDUINO CODE for Sumo Cum Laude (Sumo bot) 
#include <ArduinoRobot.h>
https://www.arduino.cc/en/Reference/RobotLibrary


  
  
	// if enemy is detected => then IR_Interrupt Enemy
  	// Align front with enemy
    
  	// Charge && stay aligned && make sure that robot is within bounds of sumo ring
    
    
    
  // if sumo ring bounds are detected => IR_Interrupt Lines/Bounds
  	// Disable enemy detection
    
    // Move backwards
    
    // Rotate 180
    
    // Re-enable enemy detection


//List Constants here
const int IR_ARRAY[] = {}
const int motor_speed = 250;
const int in1 = pinX;	//8
const int in2 = pinY;	//7
const int speedVar = pinZ;	//10

// List Variables here
bool enemyDetected = false;
int motor_degree = 0;

// List Functions here
// Moves robot straight ahead (with respect to front)
void move_straight()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  //Control Speed
  analogWrite(speedVar, motor_speed);
}

// Moves robot backwards (with respect to front)
void move_backward()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  //control Speed
  analogWrite(speedVar, motor_speed); //pin 9 pulse modulation (variable speed)
}

// Turns robot to left
void turn_left()
{
    Robot.turn(motor_degree); //make bot turn 90 degrees left
}

// Turns robot to right
void turn_right()
{
    Robot.turn(motor_degree); //make bot turn 90 degrees right
}

void turn_180()
{
    Robot.turn(180); //make bot turn 180 degrees right
}

void ir_enemy_charge(){
	while(IR_ARRAY[0] == HIGH || IR_ARRAY[1] == HIGH){
  	move_straight();
  }
  //If Enemy leaves... return to triangular movement
  loop();
}

void ir_enemy_detect(){
	//Determine while IR sensor was triggered HIGH
  //Make that IR sensor the condition for the loop
  //Assuming IR_ARRAY[0] and IR_ARRAY[1] are the true front
  if(IR_ARRAY[0] == HIGH || IR_ARRAY[1] == HIGH){
  	ir_enemy_charge();
  }
  //Assuming right side
  else if(IR_ARRAY[2] == HIGH || IR_ARRAY[3] == HIGH){
		turn_left();  	
  }
  //Assuming left side
  else if(IR_ARRAY[4] == HIGH || IR_ARRAY[5] == HIGH){
  	turn_right();
  }
  //Assuming back side
  else if(IR_ARRAY[6] == HIGH || IR_ARRAY[7] == HIGH){
  	turn_180();
  }
	
}
void ir_line_detect(){
	
}

trianglePattern(){
	while (!enemyDetected) {
    turn_left(); // LEFT
  	move_straight();
	}
	}
	
//End Listing Functions


void setup() {
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(), ir_enemy_detect, RISING)		//Because intterrupt can only detect RISING edge on MEGA board, must check condition continuously in function
  attachInterrupt(digitalPinToInterrupt(), ir_line_detect, RISING)		
  
  // Initialize pins for IR sensors
  pinMode(IR_ARRAY[0], INPUT); // Front
  pinMode(IR_ARRAY[1], INPUT); // Front
  
  pinMode(IR_ARRAY[2], INPUT); // Left
  pinMode(IR_ARRAY[3], INPUT); // Left
  
  pinMode(IR_ARRAY[4], INPUT); // Right
  pinMode(IR_ARRAY[5], INPUT); // Right
  
  pinMode(IR_ARRAY[6], INPUT); // Back
  pinMode(IR_ARRAY[7], INPUT); // Back
  
  //Initialize constructor for ArduinoRobot
  Robot.begin();

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(speedVar, OUTPUT);
}




void loop() {
	//In order to move in triangle, must start to move right, then begin shape
	motor_degree = 60;
	turn_right();
	move_straight();

	// As long as enemy is not detected, continue moving in triangular fashion
	//Break when interrupted
	//Make it a function so it can be called outside of main loop
	
	trianglePattern();
  }  



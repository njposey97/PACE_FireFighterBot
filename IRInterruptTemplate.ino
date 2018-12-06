void setup() {
  pinMode(2, INPUT);

   //If this interrupt is triggered then we have reached the edge
   //We need to make sure that the IR can trigger at tape instead of just distance
  attachInterrupt(digitalPinToInterrupt(2), printScreen, CHANGE);
  Serial.begin(9600);
}

//This is for testing, but in the finished project we need to run macro to determine whether we are at board edge or candle cirlce
void  printScreen(){
  Serial.println(digitalRead(2));
  }

void loop() {
}

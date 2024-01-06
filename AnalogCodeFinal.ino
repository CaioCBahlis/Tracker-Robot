#include <NewPing.h> // Define library for the sonars, NewPing was the library that perfomed the best for the project, besides, it has a max range for the sonars which helps it not tracking unwanted objects


const int Trig = 4; // Define Trigger pin for 1 Sonar
const int Echop = 5;  // Define Echo pin for 1 sonar
const int Trig1 = 7; // Define Trigger Pin for 2 Sonar
const int Echo1 = 6; // Define Echo Pin for 2 sonar
int R1 = 8; // Left Motor
int R2 = 9; // Left Motor
int L1 = 10; // Right Motor
int L2 = 11; // Right Motor
int DistanceParam = 4; // variable to compare the distance between the measurement of two sonars
int D1; // Variable placeholder to define sonar distance 1
int D2; // Variable placeholder to define sonar distance 2
int Relate; // Variable placeholder to define distance between distance of both sonars
int del = 500; // The delay of all functions
int vel = 180; // The velocity of the robot

NewPing ultrasonic(Trig, Echop, 50);
NewPing ultrasonic2(Trig1, Echo1, 50);
// create two objects for the sonars, so library functions can be used

void setup() {

   


}


void Turn_Left(){ 
  digitalWrite(R1, LOW);
  analogWrite(R2, vel);
  analogWrite(L1, vel);
  digitalWrite(L2, LOW);
  // make left wheel spin backwards and right wheel spin forward, so it turns left
}

void Turn_Right(){ 
  analogWrite(R1, vel);
  digitalWrite(R2, LOW);
  digitalWrite(L1, LOW);
  analogWrite(L2, vel);
  // make right wheel spin backwards and left wheel spin forward, so it turns right
}

//int Get_Filtered_Median(){
  //uint16_t CursedArray[sz] = {0,0,0,0,0};
  //int middle;


  //for(int i = 0; i < 5; i++){
    //CursedArray[i] = Sonar1.ping_cm();
  //}

  //KickSort<uint16_t>::quickSort(CursedArray, sz);

  //middle = CursedArray[2];

  //return middle;

// unused function that gets the median value from an array of measures of the sonars
// It solves the innacuracy and false positives in HCSR04 sonars



void loop() {
  
    D1 = ultrasonic.ping_cm();
    D2 = ultrasonic2.ping_cm();
    Relate = D1-D2;
    delay(del);
    // measures the distance between the two sonars and an object and calculate the difference between the measurements


  while (Relate > DistanceParam){
    Turn_Left();
    delay(del);
    D1 = ultrasonic.ping_cm();
    D2 = ultrasonic2.ping_cm();
    Relate = D1-D2;
    
    
    
  } 
  // if the difference in distance between the right sonar and and the object and the left sonar and the object is more than DistanceParameter, I want it to turn right until the distance is lesser than DistanceParameter
  // If the distance between the left sonar and the right sonar is greater than the Parameter
  // Then the robot turn left until the distance is lesser than the param
 

  while (Relate < DistanceParam*-1){
    Turn_Right();
    
    delay(del);
    D1 = ultrasonic.ping_cm();
    D2 = ultrasonic2.ping_cm();
    Relate = D1-D2;
    
    
  }

  while (D1 == 0 && D2 == 0){
    D1 = ultrasonic.ping_cm();
    D2 = ultrasonic2.ping_cm();
    Relate = D1-D2;
    delay(del);
    

    digitalWrite(R1, LOW);
    digitalWrite(R2, LOW);
    digitalWrite(L1, LOW);
    digitalWrite(L2, LOW);

  }

  // if both measurements are 0, stop

  while (Relate > DistanceParam*-1 && Relate < DistanceParam){
    D1 = ultrasonic.ping_cm();
    D2 = ultrasonic2.ping_cm();
    Relate = D1-D2;
    delay(del);
    
    analogWrite(R1, vel);
    digitalWrite(R2, LOW);
    analogWrite(L1, vel);
    digitalWrite(L2, LOW);

  }
 // if the distance of the sonars are between both DistanceParameters, go forward

}

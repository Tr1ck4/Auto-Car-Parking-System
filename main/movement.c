#include "movement.h"
// -------- MOVEMENTS --------
void forward() {

  // FRONT
  digitalWrite(IN1_F, HIGH);
  digitalWrite(IN2_F, LOW);
  digitalWrite(IN3_F, HIGH);
  digitalWrite(IN4_F, LOW);
}

void turnLeft() {
  // RIGHT wheels forrward
  digitalWrite(IN1_F, HIGH);
  digitalWrite(IN2_F, LOW);

  // LEFT wheels backward 
  digitalWrite(IN3_F, LOW);
  digitalWrite(IN4_F, HIGH);
}

void turnRight() {
  // RIGHT wheels backward
  digitalWrite(IN1_F, LOW);
  digitalWrite(IN2_F, HIGH);

  // LEFT wheels backward 
  digitalWrite(IN3_F, HIGH);
  digitalWrite(IN4_F, LOW);
}

void switchMotors() {
  if (analogRead(ENA_RIGHT) == 0 || analogRead(ENA_LEFT) == 0) {
    
  } 
  else{
    analogWrite(ENA_RIGHT, 0);
    analogWrite(ENA_LEFT, 0);
  }
}

// int handleIntersection() {
//   // 1. Move forward slightly to get the sensors past the "cross" bar
//   // This prevents the robot from getting stuck in a loop at the intersection
//   int last = millis();
//   forward();
//   delay(100);
//   while(digitalRead(Pin_right_ir) == HIGH){
//     forward();
//   }
//   return millis() - last;

//   // 2. Execute the turn
//   // Turn right until the right sensor hits the NEW line
//   while (digitalRead(Pin_right_ir) == HIGH) {
//     analogWrite(ENA_RIGHT, 200); // Lower speed for better precision
//     analogWrite(ENA_LEFT, 200);
//     turnRight();
//   }
  
//   analogWrite(ENA_RIGHT, 0);
//   analogWrite(ENA_LEFT, 0);
// }
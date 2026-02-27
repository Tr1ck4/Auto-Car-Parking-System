#include "movement.h"
// -------- MOVEMENTS --------
void forward() {

  // FRONT
  digitalWrite(IN1_F, HIGH);
  digitalWrite(IN2_F, LOW);
  digitalWrite(IN3_F, HIGH);
  digitalWrite(IN4_F, LOW);

  analogWrite(ENA_ALL, 255);
}

void turnLeft() {
  // RIGHT wheels forrward
  digitalWrite(IN1_F, HIGH);
  digitalWrite(IN2_F, LOW);

  // LEFT wheels backward 
  digitalWrite(IN3_F, LOW);
  digitalWrite(IN4_F, HIGH);

  analogWrite(ENA_ALL, 255);
}

void turnRight() {
  // RIGHT wheels backward
  digitalWrite(IN1_F, LOW);
  digitalWrite(IN2_F, HIGH);

  // LEFT wheels backward 
  digitalWrite(IN3_F, HIGH);
  digitalWrite(IN4_F, LOW);

  analogWrite(ENA_ALL, 255);
}

void stopMotors() {
  analogWrite(ENA_ALL, 0);
}
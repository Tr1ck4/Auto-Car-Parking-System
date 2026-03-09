#include "movement.h"
// -------- MOVEMENTS --------
void forward() {
  digitalWrite(IN1_F, HIGH);
  digitalWrite(IN2_F, LOW);
  digitalWrite(IN3_F, HIGH);
  digitalWrite(IN4_F, LOW);
}

void backward() {
  digitalWrite(IN1_F, LOW);
  digitalWrite(IN2_F, HIGH);
  digitalWrite(IN3_F, LOW);
  digitalWrite(IN4_F, HIGH);
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

  // LEFT wheels backward Q
  digitalWrite(IN3_F, HIGH);
  digitalWrite(IN4_F, LOW);
}


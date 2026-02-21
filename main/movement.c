#include "movement.h"
// -------- MOVEMENTS --------
void forward() {

  // FRONT
  digitalWrite(IN1_F, HIGH);
  digitalWrite(IN2_F, LOW);
  digitalWrite(IN3_F, HIGH);
  digitalWrite(IN4_F, LOW);

  // REAR
  digitalWrite(IN1_R, HIGH);
  digitalWrite(IN2_R, LOW);
  digitalWrite(IN3_R, HIGH);
  digitalWrite(IN4_R, LOW);

  analogWrite(ENA_ALL, 200);
}

void turnLeft() {

  // LEFT wheels backward
  digitalWrite(IN1_F, LOW);
  digitalWrite(IN2_F, HIGH);
  digitalWrite(IN1_R, LOW);
  digitalWrite(IN2_R, HIGH);

  // RIGHT wheels forward
  digitalWrite(IN3_F, HIGH);
  digitalWrite(IN4_F, LOW);
  digitalWrite(IN3_R, HIGH);
  digitalWrite(IN4_R, LOW);

  analogWrite(ENA_ALL, 200);
}

void stopMotors() {
  analogWrite(ENA_ALL, 0);
}
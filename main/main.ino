#include "movement.c"
#include "infra.c"

int last = 3;
bool turning = false;
int incoming = [0,0,1];
int pointer = 0;

void setup() {
  Serial.begin(9600);

  pinMode(IN1_F, OUTPUT);
  pinMode(IN2_F, OUTPUT);
  pinMode(IN3_F, OUTPUT);
  pinMode(IN4_F, OUTPUT);
  pinMode(ENA_LEFT, OUTPUT);
  pinMode(ENA_RIGHT, OUTPUT);

  pinMode(Pin_left_ir, INPUT);
  pinMode(Pin_right_ir, INPUT);

  digitalWrite(IN1_F,LOW);
  digitalWrite(IN2_F,LOW);
  digitalWrite(IN3_F,LOW);
  digitalWrite(IN4_F,LOW);
}

void loop() {
  int result = detect_line();
  Serial.println(result);
  // if (result != 0){
  //   analogWrite(ENA_RIGHT, 255);
  //   analogWrite(ENA_LEFT, 255);
  // }
  switch (result) {
    case 3: // No line detected (Lost)
      // Optional: keep moving slow or stop
      analogWrite(ENA_RIGHT, 255);
      analogWrite(ENA_LEFT, 255);
      forward();
      break;

    case 1: // Left sensor on line
      turnLeft();
      break;

    case 2: // Right sensor on line
      turnRight();
      break;

    case 0: // Intersection (Both sensors on line)
      if (incoming[pointer] == 1){
        turnRight();
        delay(2000); // play with the time
        pointer++;
      }
      else{
        forward();
        delay(400); // base on distance for the sloot
      }
      break;
  }
}

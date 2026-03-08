#include "movement.c"
#include "infra.c"

int last = 3;
bool turning = false;
String incoming = "";
int pointer = 0;

void updateCommand(String cmd){
  incoming = cmd;
  pointer = 0;
}

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

    case 0: // Intersection
      if(pointer < incoming.length()){
        int command = incoming[pointer] - '0';  
        if(command == 1){
          while(detect_line() != 1){
            turnRight();
          }
        }

        else if(command == 2){
          while(detect_line() != 2){
            turnLeft();
          }
        }

        else{
          forward();
          delay(400);
        }
        pointer++;
      }
      break;
    
  }
}

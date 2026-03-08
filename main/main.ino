#include "movement.c"
#include "infra.c"
#include "communicate.c"

#include <SoftwareSerial.h>

SoftwareSerial espSerial(10, 11); 

int last = 3;
bool turning = false;
String incoming = "2";
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

  espSerial.begin(9600);
}

void loop() {
  // if (espSerial.available()) {
  //   incoming = espSerial.readStringUntil('\n');
  //   Serial.println(incoming);  
  // }
  int result = detect_line();
  Serial.println(result);
  switch (result) {
    case 3: // No line detected (Lost)
      // Optional: keep moving slow or stop
      analogWrite(ENA_RIGHT, 255);
      analogWrite(ENA_LEFT, 255);
      forward();
      break;

    case 2: // Left sensor on line
      turnLeft();
      analogWrite(ENA_RIGHT, 200);
      analogWrite(ENA_LEFT, 200);
      break;

    case 1: // Right sensor on line
      turnRight();
      analogWrite(ENA_RIGHT, 200);
      analogWrite(ENA_LEFT, 200);
      break;

    case 0: // Intersection
      if(pointer < incoming.length()){

        int command = incoming[pointer] - '0';

        if(command == 1){  // RIGHT

          // turn until right sensor finds line
          while(detect_line() != 1){
            turnRight();
          }

          // go forward until intersection finished
          while(detect_line() != 0){
            forward();
          }
        }

        else if(command == 2){  // LEFT

          while(detect_line() != 2){
            turnLeft();
          }

          while(detect_line() != 0){
            forward();
          }
        }

        else{  // STRAIGHT

          while(detect_line() != 0){
            forward();
          }

        }

        pointer++;
      }

      break;
  }
}

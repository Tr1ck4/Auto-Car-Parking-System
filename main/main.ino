#include "movement.c"
#include "infra.c"
#include "communicate.h"

#include <SoftwareSerial.h>

// SoftwareSerial espSerial(10, 11); 

String msg = "";
int pointer = 0;
bool isPark = false;
void setup() {
  Serial.begin(9600);

  pinMode(IN1_F, OUTPUT);
  pinMode(IN2_F, OUTPUT);
  pinMode(IN3_F, OUTPUT);
  pinMode(IN4_F, OUTPUT);

  pinMode(Pin_left_ir, INPUT);
  pinMode(Pin_right_ir, INPUT);

  digitalWrite(IN1_F,LOW);
  digitalWrite(IN2_F,LOW);
  digitalWrite(IN3_F,LOW);
  digitalWrite(IN4_F,LOW);

  // espSerial.begin(9600);
  requestParking();
  // receiveParkingMessage();
}

void loop() {
  if (!isPark){
    while(msg == ""){
      if (Serial.available()) {
        msg = Serial.readStringUntil('\n');
        msg.trim();
        msg = msg.substring(5);

        Serial.print("Received: ");
        Serial.println(msg);
      }
    }

    int result = detect_line();
    Serial.println(result);
    
    switch (result) {
      case 3: // No line detected (Lost)
        // Optional: keep moving slow or stop
        forward();
        break;

      case 1: // Left sensor on line
        turnLeft();
        break;

      case 2: // Right sensor on line
        turnRight();
        break;

      case 0: // Intersection
        if(pointer < msg.length()){
          int command = msg[pointer] - '0';\
          Serial.println(msg[pointer]);
          if(command == 2){  // RIGHT
            // turn until right sensor finds line
            while(detect_line() != 2){
              turnRight();
            }
            // go forward until intersection finished
            while(detect_line() != 0){
              forward();
            }
            stop();
            occupySlot(recvBuffer.length());
            isPark = true;
          }
          else if(command == 1){  // LEFT
            while(detect_line() != 1){
              turnLeft();
            }
            while(detect_line() != 0){
              forward();
            }
            stop();
            occupySlot(recvBuffer.length());
            isPark = true;
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
}

#include "movement.c"
#include "sensor.c"
#include "infra.c"
>>>>>>> Stashed changes

void setup() {
  Serial.begin(9600);
  pinMode(ENA_ALL, OUTPUT);
  
  pinMode(IN1_F, OUTPUT);
  pinMode(IN2_F, OUTPUT);
  pinMode(IN3_F, OUTPUT);
  pinMode(IN4_F, OUTPUT);

  pinMode(IN1_R, OUTPUT);
  pinMode(IN2_R, OUTPUT);
  pinMode(IN3_R, OUTPUT);
  pinMode(IN4_R, OUTPUT);

  pinMode(Pin_left_ir, INPUT);
  pinMode(Pin_right_ir, INPUT);
}

// void loop() {
//   // turnLeft();
//   // delay(1200);
//   // stopMotors();
//   // delay(1000);
//   int L = digitalRead(Pin_left_ir);
//   int R = digitalRead(Pin_right_ir);
//   Serial.print(L);
//   Serial.print(" ");
//   Serial.println(R);
//   int result = detech_line();
//   // Serial.println(result);
//   switch (result) {
//     case 0:
//       stopMotors();
//       break;

//     case 2:
//       // code for result == 1
//       turnRight();
//       break;

//     case 1:
//       // code for result == 2
//       turnLeft();
//       break;

//     default:
//       // code if none of the above match
//       forward();
//       break;
//   }
// }

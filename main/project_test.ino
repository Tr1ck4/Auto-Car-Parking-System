// int Pin_left_ir = 11;   
// int Pin_right_ir = 10;

// void setup() {
//   pinMode(Pin_left_ir, INPUT);
//   pinMode(Pin_right_ir, INPUT);
//   Serial.begin(9600);
// }

// void loop() {
//   int valueL = digitalRead(Pin_left_ir);
//   int valueR = digitalRead(Pin_right_ir);
//   Serial.print("L:");
//   Serial.println(valueL);
//   Serial.print("R:");
//   Serial.println(valueR);
//   delay(200);
// }


// int detech_line() {
//   int L = digitalRead(Pin_left_ir);
//   int R = digitalRead(Pin_right_ir);//high->not detect line; low->detect line

//   if (L == HIGH && R == HIGH) {
//     return 0;   // both didnt detect line
//   }
//   else if (L == LOW && R == HIGH) {
//     return 1;   // left
//   }
//   else if (L == HIGH && R == LOW) {
//     return 2;   // right
//   }
//   else { // L == LOW && R == LOW
//     return 3;   // both detect
//   }
// }
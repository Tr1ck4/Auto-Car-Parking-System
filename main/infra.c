#include "infra.h"

int detect_line() {
  int L = digitalRead(Pin_left_ir);
  int R = digitalRead(Pin_right_ir); //high->not detect line; low->detect line
  

  if (L == HIGH && R == HIGH) {
    return 0;   // both didnt detect line
  }
  else if (L == LOW && R == HIGH) {
    return 1;   // left
  }
  else if (L == HIGH && R == LOW) {
    return 2;   // right
  }
  else { // L == LOW && R == LOW
    return 3;   // both detect
  }
}
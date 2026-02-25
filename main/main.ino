#include "movement.c"
#include "sensor.c"
#include <SoftwareSerial.h>
SoftwareSerial BT(2, 3);

void setup() {

  pinMode(ENA_ALL, OUTPUT);
  
  pinMode(IN1_F, OUTPUT);
  pinMode(IN2_F, OUTPUT);
  pinMode(IN3_F, OUTPUT);
  pinMode(IN4_F, OUTPUT);

  pinMode(IN1_R, OUTPUT);
  pinMode(IN2_R, OUTPUT);
  pinMode(IN3_R, OUTPUT);
  pinMode(IN4_R, OUTPUT);
}



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

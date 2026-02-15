//Define pin
#define HIGH   1
#define LOW    0
// FRONT L298N
#define ENA_F  5
#define IN1_F  6
#define IN2_F  7

#define ENB_F  10
#define IN3_F  8
#define IN4_F  9

// REAR L298N
#define ENA_R  3
#define IN1_R  4
#define IN2_R  2

#define ENB_R  11
#define IN3_R  12
#define IN4_R  13

//Movement functions

void forward();
void backward();

void turnLeft();
void turnRight();

void stopMotors();
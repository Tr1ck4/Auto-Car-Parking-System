#include <SoftwareSerial.h>
SoftwareSerial BT(2, 3);

void setup() {

}

void loop() {

}




void sendREQ() {
  BT.println("req");  
}


void sendOCP(uint8_t slot) {
  BT.print("ocp:");
  BT.println(slot);
}


uint8_t receiveFromMaster() {

  if (!BT.available()) return 0;

  uint8_t b = BT.read();

  if (b >= 1 && b <= 4) return b;

  return 0;
}
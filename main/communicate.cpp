#include "communicate.h"

String recvBuffer = "";
int assignedSlot = -1;
bool slotReady = false;

void requestParking() {
  Serial.println("REQ");
}

void occupySlot(int slot) {
  Serial.print("OCCUPY+");
  Serial.println(slot);
}

void receiveParkingMessage() {
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    msg.trim();

    Serial.print("Received: ");
    Serial.println(msg);
  }
}


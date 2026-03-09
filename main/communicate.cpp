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
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      recvBuffer.trim();
      if (recvBuffer.startsWith("SLOT+")) {
        String numStr = recvBuffer.substring(5);
        assignedSlot = numStr.toInt();
        slotReady = true;
      }
      recvBuffer = "";
    }
    else if (c != '\r') {
      recvBuffer += c;
    }
  }
}

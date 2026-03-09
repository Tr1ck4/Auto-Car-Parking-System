#include <Arduino.h>
#include "communicate.h"

void requestParking() {
  Serial.println("REQ");
}

void occupySlot(int slot) {
  Serial.print("OCCUPY+");
  Serial.println(slot);
}

void receiveParkingMessage(int *num,bool *ready) {

  while (Serial.available()) {

    char c = Serial.read();

    if (c == '\n') {

      recvBuffer.trim();

      if (recvBuffer.startsWith("SLOT+")) {

        String numStr = recvBuffer.substring(5);
        *num = numStr.toInt();
        *ready = true;
      }

      recvBuffer = "";
    }

    else if (c != '\r') {
      recvBuffer += c;
    }
  }
}

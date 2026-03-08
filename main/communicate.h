#ifndef PARKING_COMM_H
#define PARKING_COMM_H
#include <Arduino.h>

// variables
extern String recvBuffer;
extern int assignedSlot;
extern bool slotReady;

// function declarations
void requestParking();
void occupySlot(int slot);
void receiveParkingMessage();

#endif
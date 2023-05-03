#include "../../firmware.h"

/**
 * @brief Update the status screen to show what is currently going on
 * 
 * @param event Most recent Event* struct containing info on most recent changes
 * @param Pins PinStatus struct that contains info on all of the pins
 */
void updateStatusDisplay(Event* event, PinStatus* Pins[3]){
  // get device number from event
  int device = event->device;
  int frequency = event->frequency;

  if (event->isActive){
    if (!Pins[device]->isRunningEvent){
      Pins[device]->isRunningEvent = true;
      if (frequency != 0){
        writeLCD("Flashing", 8, device + 1);
      } else {
        writeLCD("On", 8, device + 1);
      }
    }
  } else {
    if (Pins[device]->isRunningEvent){
      Pins[device]->isRunningEvent = false;
      writeLCD("         ", 8, device + 1);
    }
  } 
}

/**
 * @brief Initialize the status screen with main words
 * 
 */
void initStatus(char* filename){
  char displayName[30];
  strncpy(displayName, filename, 15);
  displayName[15] = '\0';
  char* shortDisplayName = displayName + 1;

  writeLCD(shortDisplayName, 0, 0);
  writeLCD("White:", 0, 3);
  writeLCD("Red:", 0, 1);
  writeLCD("Green:", 0, 2);
}

/**
 * @brief Update the percent done indicator on the status screen
 * 
 * @param currentMinute int value of current total minutes into test
 * @param startMinute int value of the total minute of the first event start
 * @param endMinute int value of the total minute of the final event end
 */
void updateStatusPercentAndTime(int currentMinute, int startMinute, int endMinute, Time* currnetTime){
  int percent = (100 * (currentMinute- startMinute))/(endMinute-startMinute);
  if (percent < 0){
    percent = 0;
  }
  writeLCD("%",19,1);

  if (percent < 10){
    writeLCDInt(percent, 18, 1);
  } else if (percent < 100){
    writeLCDInt(percent, 17, 1);
  } else {
    writeLCDInt(percent, 16, 1);
  }

  dispTime(currnetTime, 15, 0);
}
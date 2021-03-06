//      ******************************************************************
//      *                                                                *
//      *                 Header file for Slave.ino                      *
//      *                                                                *
//      *                 Copyright (c) Josh Benson                      *
//      *                                                                *
//      ******************************************************************

#include "SerialSlave.h"
#include "SpeedyStepper.h"


#define ADDRESS 17

SpeedyStepper stepper1;
SpeedyStepper stepper2;
SpeedyStepper stepper3;
SpeedyStepper stepper4;
SpeedyStepper stepper5;
SpeedyStepper stepper6;

bool LED = false;
bool running1 = false;
bool running2 = false;
bool running3 = false;
bool running4 = false;
bool running5 = false;
bool running6 = false;
double stepperSetting = .25;
int speedSetting = 500;

void setup() {
  serialSlave.open(115200, ADDRESS, 40);
  Serial.begin(9600);
 // moveStepperHome(1, 1);

  stepper1.connectToPort(1);
  stepper1.setSpeedInStepsPerSecond(500);
  stepper1.setAccelerationInStepsPerSecondPerSecond(500);

  stepper2.connectToPort(2);
  stepper2.setSpeedInStepsPerSecond(500);
  stepper2.setAccelerationInStepsPerSecondPerSecond(500);

  stepper3.connectToPort(3);
  stepper3.setSpeedInStepsPerSecond(500);
  stepper3.setAccelerationInStepsPerSecondPerSecond(500);

  stepper4.connectToPort(4);
  stepper4.setSpeedInStepsPerSecond(500);
  stepper4.setAccelerationInStepsPerSecondPerSecond(500);

  stepper5.connectToPort(5);
  stepper5.setSpeedInStepsPerSecond(500);
  stepper5.setAccelerationInStepsPerSecondPerSecond(500);

  stepper6.connectToPort(6);
  stepper6.setSpeedInStepsPerSecond(500);
  stepper6.setAccelerationInStepsPerSecondPerSecond(500);


}

void loop() {

  if (stepper1.processMovement() && running1) {
    stepper1.disableStepper();
    running1 = false;
  }

  if (stepper2.processMovement() && running1) {
    stepper2.disableStepper();
    running2 = false;
  }

  if (stepper3.processMovement() && running1) {
    stepper3.disableStepper();
    running3 = false;
  }

  if (stepper4.processMovement() && running1) {
    stepper4.disableStepper();
    running4 = false;
  }

  if (stepper5.processMovement() && running1) {
    stepper5.disableStepper();
    running5 = false;
  }

  if (stepper6.processMovement() && running1) {
    stepper6.disableStepper();
    running6 = false;
  }
}

  Func moveStepper;
  Func stopStepper;


Callable callables[] = {
  {"moveStepper", moveStepper},
  {"disable", disable},
  {"blinkLED", blinkLED},
  {"toggleLED", toggleLED},
  {"moveStepperToPos", moveStepperToPos},
  {"moveStepperDeg", moveStepperDeg},
  {"moveStepperRev", moveStepperRev},
  {"moveStepperHome", moveStepperHome},
  {"setStepperSpeed", setStepperSpeed},
  {"setStepperAccel", setStepperAccel}
};

byte numberOfExternalCallables = sizeof(callables) / sizeof(Callable);

void moveStepperHome(byte dataLength, byte *dataArray) {

  Serial.println("running moveStepperHome");

  
  int switchPin = ((int *) (dataArray + 2))[0]; //list parameter must be switch pin
  byte stepper = dataArray[0]; //first parameter is port
  long maxDistance = 10000;
  long dir = dataArray[1]; //second parameter is direction
  float spd = 500;
 // float spd = (float)speedSetting;
  if (dir == 0) {
    dir = -1;
  }

  Serial.println("created variables");
  

  // variables hard-coded:
/*
  int switchPin = 29;
  byte stepper = 1;
  long maxDistance = 100000;
  long dir = 1;
  float spd = 500;
  if (dir == 0)
    dir = -1;
*/    
    
  switch (stepper) {
    case 1:
      Serial.println("Stepper One Case");
      stepper1.moveToHomeInSteps(dir, spd, maxDistance, switchPin);
      break;
    case 2:
      Serial.println("Stepper Two Case");
      stepper2.moveToHomeInSteps(dir, spd, maxDistance, switchPin);
      break;
    case 3:
      Serial.println("Stepper Three Case");
      stepper3.moveToHomeInSteps(dir, spd, maxDistance, switchPin);
      break;
    case 4:
      Serial.println("Stepper Four Case");
      stepper4.moveToHomeInSteps(dir, spd, maxDistance, switchPin);
      break;
    case 5:
      Serial.println("Stepper Five Case");
      stepper5.moveToHomeInSteps(dir, spd, maxDistance, switchPin);
      break;
    case 6:
      Serial.println("Stepper Six Case");
      stepper6.moveToHomeInSteps(dir, spd, maxDistance, switchPin);
      break;
  }
}

void moveStepper(byte dataLength, byte *dataArray) {

  byte stepper = dataArray[0];
  int steps = ((int *) (dataArray + 2))[0];
  if (dataArray[1] == 1) {
    steps *= -1;
  }

  switch (stepper) {
    case 1:
      stepper1.enableStepper();
      stepper1.setupRelativeMoveInSteps(steps);
      running1 = true;
      break;
    case 2:
      stepper2.enableStepper();
      stepper2.setupRelativeMoveInSteps(steps);
      running2 = true;
    case 3:
      stepper3.enableStepper();
      stepper3.setupRelativeMoveInSteps(steps);
      running3 = true;
      break;
    case 4:
      stepper4.enableStepper();
      stepper4.setupRelativeMoveInSteps(steps);
      running4 = true;
    case 5:
      stepper5.enableStepper();
      stepper5.setupRelativeMoveInSteps(steps);
      running5 = true;
      break;
    case 6:
      stepper6.enableStepper();
      stepper6.setupRelativeMoveInSteps(steps);
      running6 = true;
      break;
  }

  return("Moving Stepper");

}

void blinkLED(byte dataLength, byte *dataArray) {

  byte LEDPin = dataArray[0];
  byte waitTime = dataArray[1];

  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, HIGH);
  Serial.print("LED On");
  delay(waitTime * 30);
  digitalWrite(LEDPin, LOW);
  Serial.print("LED Off");
  delay(waitTime);

  LED = true;

}

void toggleLED(byte dataLength, byte *dataArray) {

  byte LEDPin = dataArray[0];
  byte switchState = dataArray[1];

  pinMode(LEDPin, OUTPUT);
  if (switchState == 0)
  {
    digitalWrite(LEDPin, LOW);
  }
  else if (switchState == 1)
  {
    digitalWrite(LEDPin, LOW);
  }
  else
  {
    Serial.print("LED switch state must be 0 or 1. This is the second value in dataArray");
  }

}


void disable() {
  stepper1.disableStepper();
  stepper2.disableStepper();
  stepper3.disableStepper();
  stepper4.disableStepper();
  stepper5.disableStepper();
  stepper6.disableStepper();
}


void moveStepperDeg(byte dataLength, byte *dataArray) {
  
  byte stepper = dataArray[0];
  int deg = ((int *) (dataArray + 2))[0];
  double stepsPerDeg = (200*(1/stepperSetting))/(360);
  int steps = (int) (stepsPerDeg*deg);
  if (dataArray[1] == 1) {
    steps *= -1;
  }

  
  switch (stepper) {
    case 1:
      stepper1.enableStepper();
      stepper1.setupRelativeMoveInSteps(steps);
      running1 = true;
      break;
    case 2:
      stepper2.enableStepper();
      stepper2.setupRelativeMoveInSteps(steps);
      running2 = true;
    case 3:
      stepper3.enableStepper();
      stepper3.setupRelativeMoveInSteps(steps);
      running3 = true;
      break;
    case 4:
      stepper4.enableStepper();
      stepper4.setupRelativeMoveInSteps(steps);
      running4 = true;
    case 5:
      stepper5.enableStepper();
      stepper5.setupRelativeMoveInSteps(steps);
      running5 = true;
      break;
    case 6:
      stepper6.enableStepper();
      stepper6.setupRelativeMoveInSteps(steps);
      running6 = true;
      break;
  }

  return("Moving Stepper Degrees");

}

void moveStepperRev(byte dataLength, byte *dataArray) {
  
  byte stepper = dataArray[0];
  int rev = ((int *) (dataArray + 2))[0];
  double stepsPerRev = 200*(1/stepperSetting);
  int steps = (int) (stepsPerRev*rev);
  if (dataArray[1] == 1) {
    steps *= -1;
  }

  switch (stepper) {
    case 1:
      stepper1.enableStepper();
      stepper1.setupRelativeMoveInSteps(steps);
      running1 = true;
      break;
    case 2:
      stepper2.enableStepper();
      stepper2.setupRelativeMoveInSteps(steps);
      running2 = true;
    case 3:
      stepper3.enableStepper();
      stepper3.setupRelativeMoveInSteps(steps);
      running3 = true;
      break;
    case 4:
      stepper4.enableStepper();
      stepper4.setupRelativeMoveInSteps(steps);
      running4 = true;
    case 5:
      stepper5.enableStepper();
      stepper5.setupRelativeMoveInSteps(steps);
      running5 = true;
      break;
    case 6:
      stepper6.enableStepper();
      stepper6.setupRelativeMoveInSteps(steps);
      running6 = true;
      break;
  }

  return("Moving Stepper Revolutions");

}

void setStepperSpeed(byte dataLength, byte *dataArray) {
  int speedStepper = ((int *) (dataArray + 2))[0];
  byte stepper = dataArray[0];
  speedSetting = speedStepper;
  
  switch (stepper) {
    case 1:
      stepper1.setSpeedInStepsPerSecond(speedStepper);
      break;
    case 2:
      stepper2.setSpeedInStepsPerSecond(speedStepper);
      break;
    case 3:
      stepper3.setSpeedInStepsPerSecond(speedStepper);
      break;
    case 4:
      stepper4.setSpeedInStepsPerSecond(speedStepper);
      break;
    case 5:
      stepper5.setSpeedInStepsPerSecond(speedStepper);
      break;
    case 6:
      stepper6.setSpeedInStepsPerSecond(speedStepper);
      break;
  }
}

//Some parameters hard coded for ease of use




  

void setStepperAccel(byte dataLength, byte *dataArray) {
  int accelStepper = ((int *) (dataArray + 2))[0];
  byte stepper = dataArray[0];
  
  switch (stepper) {
    case 1:
      stepper1.setAccelerationInStepsPerSecondPerSecond(accelStepper);
      break;
    case 2:
      stepper2.setAccelerationInStepsPerSecondPerSecond(accelStepper);
      break;
    case 3:
      stepper3.setAccelerationInStepsPerSecondPerSecond(accelStepper);
      break;
    case 4:
      stepper4.setAccelerationInStepsPerSecondPerSecond(accelStepper);
      break;
    case 5:
      stepper5.setAccelerationInStepsPerSecondPerSecond(accelStepper);
      break;
    case 6:
      stepper6.setAccelerationInStepsPerSecondPerSecond(accelStepper);
      break;
  }
}

void moveStepperToPos(byte dataLength, byte *dataArray) {

  byte stepper = dataArray[0];
  int steps1;
  int steps2;
  int steps;
  int currentPosSteps;
  switch (stepper) {
    case 1:
      currentPosSteps = stepper1.getCurrentPositionInSteps();
      break;
    case 2:
      currentPosSteps = stepper2.getCurrentPositionInSteps();
      break;
    case 3:
      currentPosSteps = stepper3.getCurrentPositionInSteps();
      break;
    case 4:
      currentPosSteps = stepper4.getCurrentPositionInSteps();
      break;
    case 5:
      currentPosSteps = stepper5.getCurrentPositionInSteps();
      break;
    case 6:
      currentPosSteps = stepper6.getCurrentPositionInSteps();
      break;
  }
  int finalPosSteps = ((int *) (dataArray + 2))[0];
  bool longways = false;
  
  if (dataArray[1] == 1) {
    longways = true;
  }

  steps1 = currentPosSteps - finalPosSteps;
  steps2 = finalPosSteps - currentPosSteps;
  if(longways == true)
  {
      if((abs(steps1))>(abs(steps2)))
      {
        steps = steps1;
      }
      else
      {
        steps = steps2;
      }
  }
  else
  {
    if((abs(steps1))>(abs(steps2)))
      {
        steps = steps2;
      }
      else
      {
        steps = steps1;
      }
  }

  switch (stepper) {
    case 1:
      stepper1.enableStepper();
      stepper1.setupRelativeMoveInSteps(steps);
      running1 = true;
      break;
    case 2:
      stepper2.enableStepper();
      stepper2.setupRelativeMoveInSteps(steps);
      running2 = true;
    case 3:
      stepper3.enableStepper();
      stepper3.setupRelativeMoveInSteps(steps);
      running3 = true;
      break;
    case 4:
      stepper4.enableStepper();
      stepper4.setupRelativeMoveInSteps(steps);
      running4 = true;
    case 5:
      stepper5.enableStepper();
      stepper5.setupRelativeMoveInSteps(steps);
      running5 = true;
      break;
    case 6:
      stepper6.enableStepper();
      stepper6.setupRelativeMoveInSteps(steps);
      running6 = true;
      break;
  }

  return("Moving Stepper Position");

}
  

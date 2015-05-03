/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.
 
 modified 8 Nov 2013
 by Scott Fitzgerald
 http://arduino.cc/en/Tutorial/Sweep
 */

#include <Servo.h> 

#define RARM 0
#define LARM 1
#define RLEG 2
#define LLEG 3
#define SHOULDERS 4
#define HIPS 5

// Create servo objects to control servos
Servo servoRA, servoLA,
servoRL, servoLL,
servoS, servoH; 

int startPos[6]; // positions of the 6 servos

boolean isSit = false; // sitting or not
boolean isWaiting = true; // waiting for a command or not
byte kIn = 255; // for reading bytes on the serial port


void setup() 
{ 
  // Open serial port
  Serial.begin(9600);
  
  // Attach servos on pins to the servo objects
  servoRA.attach(3);   
  servoLA.attach(5);
  servoRL.attach(6);
  servoLL.attach(9);
  servoS.attach(10);
  servoH.attach(11);
  
  // Starting positions for servos
  servoRA.write(90);
  servoLA.write(90);
  servoRL.write(80);
  servoLL.write(100);
  servoS.write(90);
  servoH.write(90);

  delay(1000);  
}


void loop() 
{
  // read input
  if (isWaiting)
    kIn = Serial.read();
  isWaiting = true;

  // execute command
  if (kIn == 200) Sit(); // Sit and mimic arm movements
  else if (kIn == 201) Walk(); // Walk around
  else if (kIn == 202) Stand(); // Stand up
  else if (kIn == 203) Shake(); // Shake ass
  else if (kIn == 204) Jump(); // Crawl forward
  else if (kIn == 205) Mimic(); // Stand and mimic arm movements
//  else if (kIn == 205) Flip(); // Try to recover after falling on back
}

// Move smoothly from current position to pos
// over a time interval of moveDelay*20 milliseconds
void SmoothMove(int pos[], int moveDelay) {
    GetCurrent(startPos); // read current positions of servos
    
    // Reverse left arm and left leg servos
    pos[LARM] = 180 - pos[LARM];
    pos[LLEG] = 180 - pos[LLEG];
  
    // Gradual movement towards the final position
    for (int i = 19; i > -1; i--) {
      delay(moveDelay);
      if (pos[RARM] > -1 && pos[RARM] < 181) 
        servoRA.write(pos[RARM] - (i*(pos[RARM]-startPos[RARM]))/20);
      if (pos[LARM] > -1 && pos[LARM] < 181) 
        servoLA.write(pos[LARM] - (i*(pos[LARM]-startPos[LARM]))/20);
      if (pos[RLEG] > -1 && pos[RLEG] < 181) 
        servoRL.write(pos[RLEG] - (i*(pos[RLEG]-startPos[RLEG]))/20);
      if (pos[LLEG] > -1 && pos[LLEG] < 181) 
        servoLL.write(pos[LLEG] - (i*(pos[LLEG]-startPos[LLEG]))/20);
      if (pos[SHOULDERS] > -1 && pos[SHOULDERS] < 181) 
        servoS.write(pos[SHOULDERS] - (i*(pos[SHOULDERS]-startPos[SHOULDERS]))/20);
      if (pos[HIPS] > -1 && pos[HIPS] < 181) 
        servoH.write(pos[HIPS] - (i*(pos[HIPS]-startPos[HIPS]))/20);
    }
//  }
}

// Read current positions of servos
void GetCurrent(int curPos[]) {
  curPos[RARM] = servoRA.read();
  curPos[LARM] = servoLA.read();
  curPos[RLEG] = servoRL.read();
  curPos[LLEG] = servoLL.read();
  curPos[SHOULDERS] = servoS.read();
  curPos[HIPS] = servoH.read();
}

// Return an array of six servo positions
int *SetNewPos(int a0, int a1, int a2, int a3, int a4, int a5) {
  int newPos[6];

  newPos[RARM] = a0;
  newPos[LARM] = a1;
  newPos[RLEG] = a2;
  newPos[LLEG] = a3;
  newPos[SHOULDERS] = a4;
  newPos[HIPS] = a5;

  return newPos;
}

// Sit and mimic arm movements
void Sit() {
  byte rightArm = 90;
  byte leftArm = 90;
  
  // Move into sitting position
  SmoothMove(SetNewPos(90, 90, 80, 80, 90, 90), 25);
  SmoothMove(SetNewPos(-1, -1, 150, 150, -1, -1), 25);
  SmoothMove(SetNewPos(-1, -1, 105, 105, -1, -1), 25);

  isSit = true;
  
  // Assign serial input bytes to arm positions until it reads > 180
  while (true) {
    if (Serial.available() >= 2) {
      
      // Read in for right arm
      kIn = Serial.read();
      rightArm = kIn;
      if (rightArm > 180) {
        isWaiting = false;
        break;
      }
      
      // Read in for left arm
      kIn = Serial.read();
      leftArm = kIn;
      if (leftArm > 180) {
        isWaiting = false;
        break;
      }
    }
    
    // Update arm positions
    SmoothMove(SetNewPos(rightArm, leftArm, -1, -1, -1, -1), 0);
  }
}

// Stand up on all fours from sitting position
void Stand() {
  SmoothMove(SetNewPos(90, 90, 105, 105, 90, 90), 25);
  SmoothMove(SetNewPos(180, 180, -1, -1, -1, -1), 25);
  SmoothMove(SetNewPos(-1, -1, 180, 180, -1, -1), 25);
  SmoothMove(SetNewPos(-1, -1, 150, 150, -1, -1), 25);
  SmoothMove(SetNewPos(-1, -1, 80, 80, -1, -1), 25);
  SmoothMove(SetNewPos(90, 90, -1, -1, -1, -1), 25);

  isSit = false;
}

// Walk by swivelling shoulders and hips
void Walk() {
  if (isSit)
    Stand();

  SmoothMove(SetNewPos(90, 90, 80, 80, 90, 90), 25);

  for (int i = 0; i < 8; i++) {
    SmoothMove(SetNewPos(-1, -1, -1, -1, 110, 70), 10);
    delay(500);
    SmoothMove(SetNewPos(-1, -1, -1, -1, 70, 110), 10);
    delay(500);
    if (Serial.available() >= 1) {
      kIn = Serial.read();
      isWaiting = false;
      break;
    }
  }
}

// Map arm movements to arm, shoulder, and leg servos while standing
void Mimic() {
  if (isSit)
    Stand();
  
  byte rightArm = 90;
  byte leftArm = 90;
  byte shoulders = 90;
  byte legs;

  isSit = false;
  
  // Assign serial input bytes to arm positions until it reads > 180
  while (true) {
    if (Serial.available() >= 2) {
      
      // Read in for right arm
      kIn = Serial.read();
      rightArm = kIn;
      if (rightArm > 180) {
        isWaiting = false;
        break;
      }
      
      // Read in for left arm
      kIn = Serial.read();
      leftArm = kIn;
      if (leftArm > 180) {
        isWaiting = false;
        break;
      }
    }
    
    // Adjust shoulders to swivel with the higher arm
    shoulders = 90 + (leftArm - rightArm)/2;
    
    // Set leg angles to be the average of the two arm angles
    legs = (leftArm + rightArm)/2;
    
    // Update servo positions
    SmoothMove(SetNewPos(rightArm, leftArm, legs, legs, shoulders, -1), 0);
    
    // Move only arms and shoulders
//    SmoothMove(SetNewPos(rightArm, leftArm, -1, -1, shoulders, -1), 0);
  }
}


// Free your mind and your ass will follow
void Shake() {
  if (isSit)
    Stand();
  
  SmoothMove(SetNewPos(90, 90, 80, 80, 90, 90), 25);

  for (int i = 0; i < 8; i++) {
    SmoothMove(SetNewPos(-1, -1, 75, 105, -1, 70), 10);
    delay(50);
    SmoothMove(SetNewPos(-1, -1, 105, 75, -1, 110), 10);
    delay(50);
    if (Serial.available() >= 1) {
      kIn = Serial.read();
      isWaiting = false;
      break;
    }
  }
}

// Crawl forward
void Jump() {
  for (int i = 0; i < 6; i++) {
    SmoothMove(SetNewPos(90, 90, 90, 90, 90, 90), 25);
    SmoothMove(SetNewPos(180, 180, 130, 130, -1, -1), 25);
    delay(500);
    SmoothMove(SetNewPos(90, 90, 40, 40, -1, -1), 0);
    if (Serial.available() >= 1) {
      kIn = Serial.read();
      isWaiting = false;
      break;
    }
  }
}


// The following attempt to flip over was unsuccessful
// Recover if fallen on back
//void Flip() {
//  SmoothMove(SetNewPos(90, 90, 90, 90, 90, 90), 25);
//  SmoothMove(SetNewPos(-1, -1, -1, -1, 0, 150), 25);
//  SmoothMove(SetNewPos(30, 30, -1, -1, -1, -1), 0);
//  SmoothMove(SetNewPos(180, 180, 0, 0, -1, -1), 25);
//  SmoothMove(SetNewPos(-1, -1, -1, -1, 30, -1), 25);
//  SmoothMove(SetNewPos(-1, 90, 90, 90, -1, 30), 0);
//  delay(1000);
//  SmoothMove(SetNewPos(-1, -1, -1, -1, 90, -1), 25);
//  delay(1000);
//  
//  SmoothMove(SetNewPos(-1, -1, -1, -1, -1, 0), 25);
//  delay(1000);
//  SmoothMove(SetNewPos(-1, -1, 110, 110, -1, -1), 25);
//  delay(1000);
//  SmoothMove(SetNewPos(120, -1, -1, -1, -1, -1), 25);
//  delay(1000);
//  SmoothMove(SetNewPos(90, -1, -1, -1, 60, -1), 25);
//}



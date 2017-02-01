/* stABLE Control Program
 *  
 *  BME 161 - Fall 2016
 *  University of Waterloo
 *  Department of Systems Design
 *  
 *  Written by: Megan YanYan Tran, 20659804, 1A
 *              Jerry Liu,         20663128, 1A
 *  Started: Nov 13, 2016
 */

// set pin numbers:
const int ledLeft = 2;
const int ledTopLeft = 3;
const int ledTopRight = 4;
const int ledRight = 5;

const int rButtonPin = 6;
const int lButtonPin = 7;

const int accelX = A0;
const int accelY = A1;

int rButtonState = 0;
int lButtonState = 0;

int aXBaseline;
int aYBaseline;

int aXValue;
int aYValue;
int baseline;
double aMag;

double reactionTimeR;
double stddevR;
double reactionTimeL;
double stddevL;

void setup() {
  Serial.begin(9600);

  pinMode(ledLeft, OUTPUT);
  pinMode(ledTopLeft, OUTPUT);
  pinMode(ledTopRight, OUTPUT);
  pinMode(ledRight, OUTPUT);

  pinMode(accelX, INPUT);
  pinMode(accelY, INPUT);
  pinMode(rButtonPin, INPUT);
  pinMode(lButtonPin, INPUT);
  
  calibrate();

  // Output accelerometer data from x and y into port
  //Serial.println("X         Y");
  Serial.println("Reaction time program");
  randomSeed(analogRead(1));
}

void loop() {

  //allLedsOn();

  // TODO: create method for button pushes to indicate which foot the accelerometer is on
  
  lButtonState = digitalRead(lButtonPin);
  rButtonState = digitalRead(rButtonPin);
  
  if (rButtonState == 1)
  {
    reactionTimeR = conductReactionTest(rButtonState);
    //Serial.print("AVERAGE REACTION TIME: ");
    //Serial.println(reactionTimeR);
  } else {
    reactionTimeL = conductReactionTest(rButtonState);
    //Serial.print("AVERAGE REACTION TIME: ");
    //Serial.println(reactionTimeL);
  }

  

  delay(100);
  
}

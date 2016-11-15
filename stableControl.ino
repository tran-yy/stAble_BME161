/* stAble Control Program
 *  
 *  BME 161 - Fall 2016
 *  University of Waterloo
 *  Department of Systems Design
 *  
 *  Written by: Megan YanYan Tran, 20659804, 1A
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
const int flexPin = A2;

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
}

void loop() {

  //allLedsOn();

  // TODO: enable button pushes to control which test to conduct
  
  lButtonState = digitalRead(lButtonPin);
  rButtonState = digitalRead(rButtonPin);
  
  if (lButtonState == 1 || rButtonState == 1)
    conductReactionTest(rButtonState);

  // Must be reset since it is maintained
  lButtonState = 0;
  rButtonState = 0;
  /*if (lButtonState && rButtonState) {
    calibrate();
  }*/ /*else if (lButtonState != rButtonState) {
    //conductReactionTest(rButtonState);
    lButtonState = 0;
    rButtonState = 0;
  }*/

  /*if (lButtonState == 1) {
    turnOff (ledLeft);
  }else if (rButtonState == 1) {
    turnOff (ledRight);
  }*/
  if (digitalRead(ledLeft == HIGH))
  {
    readWriteLed(ledLeft);
  }
  delay(200);
  
}

// ------------------------------------------------------------------------------------
/* HELPER METHODS */

// TODO: Calibrate to get the starting baseline x and y values
void calibrate() {
  allLedsOn();

  delay(2000);

  aXBaseline = analogRead(accelX);
  aYBaseline = analogRead(accelY);
  baseline = getBaseline();
  aMag = baseline;

  delay(1000);

  allLedsOff();
}

double getBaseline() {
  aXBaseline = analogRead(accelX);
  aYBaseline = analogRead(accelY);
  return calculateMagnitude(aXBaseline, aYBaseline);
}

void allLedsOn() {
  digitalWrite(ledLeft, HIGH);
  digitalWrite(ledRight, HIGH);
  digitalWrite(ledTopLeft, HIGH);
  digitalWrite(ledTopRight, HIGH);
}

void allLedsOff() {
  digitalWrite(ledLeft, LOW);
  digitalWrite(ledRight, LOW);
  digitalWrite(ledTopLeft, LOW);
  digitalWrite(ledTopRight, LOW);
}

void startLights() {
  for (int i = 0; i < 5; i++) {
    allLedsOn();
    delay (200);
    allLedsOff();
    delay(300);
  }
}

void turnOn( int pinNum ) {
  digitalWrite(pinNum, HIGH);
}

void turnOff( int pinNum ) {
  digitalWrite(pinNum, LOW);
}


// Calculates the magnitude of the resultant acceleration vector between x and y
double calculateMagnitude( int x, int y ){
  return sqrt( pow(x,2) + pow(y,2) );
}

// Calculates average of values in an array
double average( int values[] ){
  double total = 0;
  for (int i = 0; i < sizeof(values); i++) {
    total += values[i];
  }

  return total/sizeof(values);
}

// Calculates the standard deviation of an array of values and their average
double stddev( int values[], double mean ) {
  double total = 0;
  for (int i = 0; i < sizeof(values); i++){
    total += pow(values[i] - mean, 2);
  }

  return sqrt(total/sizeof(values));
}

void printTimes( int values[] ) {
  for (int i = 0; i < sizeof(values); i++) {
    Serial.println(values[i]);
  }
}

// ------------------------------------------------------------------------------------
/* FUNCTIONAL METHODS */

// This method returns the reaction time of the user after an LED is lit.
// Pre: pinNum is a pin connected to an LED.
// Post: reaction time is returned in milliseconds.
int getReactionTime( int pinNum ){
  int startTime;
  int endTime;
  double prevReading = getBaseline();

  //Serial.println("Get ready" );
  //delay (2000);
  
  turnOn(pinNum);
  startTime = millis();
  
  while (true) {
    aXValue = analogRead(accelX);
    aYValue = analogRead(accelY);
    aMag = calculateMagnitude(aXValue, aYValue);

    //Serial.println(aMag);

    if ( abs (prevReading - aMag) > 25 )
    {
      //Serial.println("Ya moved");
      endTime = millis();
      break;
    }
    prevReading = aMag; 
    delay(50);
  }

  turnOff(pinNum);
  
  Serial.print(endTime-startTime);
  Serial.println(" ms");
  
  return (endTime - startTime);
}


// Method to conduct the reaction tests, 10 random movements with 5 foot movements per foot
// Calls the appropriate method for the foot.
void conductReactionTest( bool rightFoot ){
  startLights();
  if (rightFoot) {
    Serial.println("Conducting test on the right foot");
    rightTest();    
  } else {
    Serial.println("Conducting test on the left foot");
    leftTest();
  }
}


// Method lights up an LED as though it were to test the left foot
void falseTest( int pinNum ){
  turnOn(pinNum);
  delay(1000);
  turnOff(pinNum);
}


// Conducts right-test and returns mean reaction time
// Assumes the accelerometer is on the right foot
void rightTest (){
  int reactionTimes[5];
  reactionTimes[0] = getReactionTime(ledRight);
  delay(5000);
  falseTest( ledTopLeft );
  delay(5000);
  reactionTimes[1] = getReactionTime(ledTopRight);
  delay(5000);
  falseTest( ledLeft );
  delay(5000);
  reactionTimes[2] = getReactionTime(ledRight);
  delay(5000);
  falseTest( ledLeft);
  delay(5000);
  reactionTimes[3] = getReactionTime(ledRight);
  delay(5000);
  falseTest( ledTopLeft );
  delay(5000);
  falseTest( ledTopLeft );
  delay(5000);
  reactionTimes[4] = getReactionTime(ledTopRight);
  delay(5000);
  
  reactionTimeR = average(reactionTimes);
  stddevR = stddev(reactionTimes, reactionTimeR);
  
  printTimes(reactionTimes);
  Serial.print("Average time (ms): ");
  Serial.println (reactionTimeR);
  Serial.print("Standard deviation: ");
  Serial.println(stddevR);
}

void leftTest() {
  int reactionTimes[5];
  delay(5000);
  reactionTimes[0] = getReactionTime(ledLeft);
  delay(5000);
  falseTest( ledTopRight );
  delay(5000);
  reactionTimes[1] = getReactionTime(ledTopLeft);
  delay(5000);
  falseTest( ledRight );
  delay(5000);
  reactionTimes[2] = getReactionTime(ledLeft);
  delay(5000);
  falseTest( ledRight);
  delay(5000);
  reactionTimes[3] = getReactionTime(ledLeft);
  delay(5000);
  falseTest( ledTopRight );
  delay(5000);
  falseTest( ledTopRight );
  delay(5000);
  reactionTimes[4] = getReactionTime(ledTopLeft);
  delay(5000);
  
  reactionTimeL = average(reactionTimes);
  stddevL = stddev(reactionTimes, reactionTimeL);
  
  Serial.print("Average time (ms): ");
  Serial.println (reactionTimeL);
  Serial.print("Standard deviation: ");
  Serial.println(stddevL);
}

void readWriteLed(int led)
{
  ledStrength = analogRead(flexPin);
  value = map(value, 700, 900, 0, 255);
  analogWrite(led, value);
}
}


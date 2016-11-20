/* stABLE Control Program

    BME 161 - Fall 2016
    University of Waterloo
    Department of Systems Design

    Written by: Megan YanYan Tran, 20659804, 1A
    Started: Nov 13, 2016
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
}

void loop() {

  //allLedsOn();

  // TODO: enable button pushes to control which test to conduct

  lButtonState = digitalRead(lButtonPin);
  rButtonState = digitalRead(rButtonPin);

  //Serial.print(lButtonState);
  //Serial.print("      ");
  //Serial.println(rButtonState);

  if (lButtonState == 1 || rButtonState == 1)
  {
    conductReactionTest(rButtonState);
  }

  // Must be reset since it is maintained
  //lButtonState = 0;
  //rButtonState = 0;

  delay(200);

}

// ------------------------------------------------------------------------------------
/* FUNCTIONAL METHODS */

// This method returns the reaction time of the user after an LED is lit.
// Pre: pinNum is a pin connected to an LED.
// Post: reaction time is returned in milliseconds.
int getReactionTime( int pinNum ) {
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
      Serial.println("Ya moved");
      endTime = millis();
      break;
    }
    prevReading = aMag;
    delay(10);
  }

  turnOff(pinNum);

  Serial.print(endTime-startTime);
  Serial.println(" ms");

  return (endTime - startTime);
}


// Method to conduct the reaction tests, 10 random movements with 5 foot movements per foot
// Calls the appropriate method for the foot.
void conductReactionTest( bool rightFoot ) {
  if (rightFoot) {
    Serial.println("Conducting test on the right foot");
    startLights();
    rightTest();
  } else {
    Serial.println("Conducting test on the left foot");
    startLights();
    leftTest();
  }
}



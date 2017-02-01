// TODO: Soft code the array size in average() and stddev() methods

/* HELPER METHODS */
 double nonFallerReactionMean = 858;
double nonFallerReactionStddev = 123;
double fallerReactionMean = 970;
double fallerReactionStddev = 228;
// Source: http://www.istoppfalls.eu/cms/upload/pdf/0_Choice_stepping_printversion.pdf

// Calibrate to get the starting baseline x and y values
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
    delay (500);
    allLedsOff();
    delay(500);
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
double average( int values[5] ){
  double total = 0;
  for (int i = 0; i < 5; i++) {
    total += values[i];
  }

  return total/5.0;
}

// Calculates the standard deviation of an array of values and their average
double stddev( int values[], double mean ) {
  double total = 0;
  for (int i = 0; i < 5; i++){
    total += pow(values[i] - mean, 2);
  }

  return sqrt(total/5.0);
}
 
void printTimes( int values[] ) {
  for (int i = 0; i < 5; i++) {
    Serial.print(values[i]);
    Serial.println(" ms");
  }
}
 
double zScore( double userMean, double normMean, double normStddev)
{
  return (userMean-normMean)/normStddev;
}
 
bool reactionClassification (double reactionMean) {
  if (reactionMean <= 900) {
    return false;
   }   return true;
}
 

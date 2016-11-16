// TODO: Randomize the tests

// Ultimate todo: 2 Accelerometers


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

  printTimes(reactionTimes);
  
  Serial.print("Average time (ms): ");
  Serial.println (reactionTimeL);
  Serial.print("Standard deviation: ");
  Serial.println(stddevL);
}


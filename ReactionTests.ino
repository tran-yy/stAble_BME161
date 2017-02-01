int randNum;

// ------------------------------------------------------------------------------------
/* FUNCTIONAL METHODS */

// Method to conduct the reaction tests, 10 random movements with 5 foot movements per foot.
double conductReactionTest( bool rightFoot ){
  int rightTests = 0;
  int leftTests = 0;

  int topSide = 0;
  int rightLeft = 0;

  int times[5];

  bool conducted = false;

  startLights();
  Serial.print("Conducting test, accelerometer on ");
  if (rightFoot) Serial.println("right");
  else Serial.println("left");
  delay(3000);
  Serial.println("GET READY!");
  

  delay(3000);
  
  while (rightTests < 5 || leftTests < 5) {
    rightLeft = random(0,2); // 0 = right, 1 = left
    topSide = random(0,2); // 0 = top, 1 = side

    /*Serial.print("right tests: ");
    Serial.println(rightTests);
    Serial.print("left tests: ");
    Serial.println(leftTests);
    Serial.print("Rightleft");
    Serial.println(rightLeft);
    Serial.print("topside");
    Serial.println(topSide);
    */

    // Rights tests conducted
    if (rightLeft == 0 && rightTests < 5) {

      if (rightFoot) {
        if (topSide == 0)     
          times[rightTests] = getReactionTime(ledTopRight);
        else if (topSide == 1) 
          times[rightTests] = getReactionTime(ledRight); 
      } 
      else {
        if (topSide == 0)
          falseTest(ledTopRight);
        else
          falseTest(ledRight);
      }

      rightTests++;
      conducted = true;
    }

    // Left tests conducted
    else if (rightLeft == 1 && leftTests < 5) {

      if (!rightFoot) {
        if (topSide == 0)       
          times[leftTests] = getReactionTime(ledTopLeft);
        else if (topSide == 1)  
          times[leftTests] = getReactionTime(ledLeft);
      }
      else {
        if (topSide == 0)
          falseTest(ledTopLeft);
        else
          falseTest(ledLeft);
      }

      leftTests++;
      conducted = true;
    }

    if (conducted) delay (4000);
    conducted = false;
  
  }
  
  // Return average
  double avg = average(times);
  double stdDev = stddev(times, avg);
  Serial.print("AVERAGE REACTION TIME: ");
  Serial.println(avg);

  Serial.println("AVERAGE REACTION TIME FOR FALLERS: 970 ms" );
  Serial.println("AVERAGE REACTION TIME FOR NON-FALLERS: 858 ms");
  Serial.print("Reaction time indicates patient ");
  if (avg > 858)
  {
    Serial.println("may be at risk for falls.");
  }
  else
  {
    Serial.println("may not be at risk for falls.");
  }

  Serial.print("STDDEV: ");
  Serial.println(stdDev);

  
  return average(times);
}

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
  int count = -1;
  while (true) {
    aXValue = analogRead(accelX);
    aYValue = analogRead(accelY);
    aMag = calculateMagnitude(aXValue, aYValue);
    
    Serial.println(accelX);
    Serial.println(accelX);

    if (abs (prevReading - aMag) > 13 ) {
      //Serial.println("Movement detected");
      endTime = millis();
      count =-1;
      break;
    }
    if(count == -1) {
      prevReading = aMag; 
    }
    count++;
    delay(10);
  }

  turnOff(pinNum);
  
  //Serial.print("Time for this trial: ");
  Serial.print(endTime-startTime);
  Serial.println(" ms");
  Serial.println();
  
  return (endTime - startTime);
}


// Method lights up an LED as though it were to test the left foot
void falseTest( int pinNum ){
  turnOn(pinNum);
  delay(1000);
  turnOff(pinNum);
}

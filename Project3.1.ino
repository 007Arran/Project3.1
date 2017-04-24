#include <SparkFun_ADXL345.h>         // SparkFun ADXL345 Library

ADXL345 adxl = ADXL345();             // USE FOR I2C COMMUNICATION

void setup() {
  Serial.begin(9600);                 // Start the serial terminal
  Serial.println("Booting Up...");
  Serial.println();
  
  adxl.powerOn();                     // Power on the ADXL345

  adxl.setRangeSetting(4);            // Give the range settings

  //adxl.setSpiBit(0);                // Aren't using SPI but idk if this needs to be in there
   
  adxl.setActivityXYZ(1, 1, 1);       // For turning on/off axiis for activity (X, Y, Z) 1 == On, 0 == Off
  adxl.setActivityThreshold(75);      // 62.5mg per increment
 
  adxl.setInactivityXYZ(1, 0, 0);     // For turning on/off axiis for inactivity (X, Y, Z) 1 == On, 0 == Off
  adxl.setInactivityThreshold(75);    // 62.5mg per increment
  adxl.setTimeInactivity(100);        // 100 Seconds of no activity starts inactivity

  adxl.setTapDetectionOnXYZ(1, 1, 1); // Detect taps in the directions turned ON "adxl.setTapDetectionOnX(X, Y, Z);" (1 == ON, 0 == OFF)
 
  // Set values for what is considered a TAP and what is a DOUBLE TAP (0-255)
  adxl.setTapThreshold(50);           // 62.5 mg per increment
  adxl.setTapDuration(15);            // 625 μs per increment
  adxl.setDoubleTapLatency(80);       // 1.25 ms per increment
  adxl.setDoubleTapWindow(200);       // 1.25 ms per increment
 
  // Set values for what is considered FREE FALL (0-255)
  adxl.setFreeFallThreshold(5);       // (5 - 9) recommended - 62.5mg per increment
  adxl.setFreeFallDuration(30);       // (20 - 70) recommended - 5ms per increment
 
  // Setting all interupts to take place on INT1 pin
  //adxl.setImportantInterruptMapping(1, 1, 1, 1, 1);     // Sets "adxl.setEveryInterruptMapping(single tap, double tap, free fall, activity, inactivity);" 
                                                        // Accepts only 1 or 2 values for pins INT1 and INT2. This chooses the pin on the ADXL345 to use for Interrupts.
                                                        // This library may have a problem using INT2 pin. Default to INT1 pin.
  
  // Turn on Interrupts for each mode (1 == ON, 0 == OFF)
  adxl.InactivityINT(1);
  adxl.ActivityINT(1);
  adxl.FreeFallINT(1);
  adxl.doubleTapINT(1);
  adxl.singleTapINT(1);
  
  //Test for savingjfkldsjfkldsjlaf;
}

void loop() {
  // put your main code here, to run repeatedly:
  // Accelerometer Readings
  int x,y,z;   
  adxl.readAccel(&x, &y, &z);

  ADXL_ISR(); 
}

void ADXL_ISR() {

    // getInterruptSource clears all triggered actions after returning value
    // Do not call again until you need to recheck for triggered actions
    byte interrupts = adxl.getInterruptSource();
  
    // Free Fall Detection
    if(adxl.triggered(interrupts, ADXL345_FREE_FALL)){
    Serial.println("*** FREE FALL ***");
    //add code here to do when free fall is sensed
    }
    
    // Activity
    if(adxl.triggered(interrupts, ADXL345_ACTIVITY)){
    Serial.println("*** ACTIVITY ***"); 
    //add code here to do when activity is sensed
    }
   
    // Tap Detection
    if(adxl.triggered(interrupts, ADXL345_SINGLE_TAP)){
    Serial.println("*** TAP ***");
       //add code here to do when a tap is sensed
    } 

  

}


// Adding the libraries
#include <SparkFun_ADXL345.h>
#include <Ultrasonic.h>

// Setting up the accelerometer and ultrasonic sensors
Ultrasonic ultrasonic(2, 3);
ADXL345 adxl = ADXL345(); 

// Setting up the flex sensor
const int flexpin = 0; 

void setup() {
    Serial.begin(9600);                 // Start the serial terminal
    Serial.println("Booting Up...");
    Serial.println();
  
    adxl.powerOn();                     // Power on the sensor

    adxl.setRangeSetting(4);            // Give the range settings in G
   
    adxl.setActivityXYZ(1, 1, 1);       // For turning on/off axiis for activity (X, Y, Z) 1 == On, 0 == Off
    adxl.setActivityThreshold(75);      // 62.5mg per increment

    adxl.setTapDetectionOnXYZ(1, 1, 1); // Detect taps in the directions turned ON "adxl.setTapDetectionOnX(X, Y, Z);" (1 == ON, 0 == OFF)
 
    // Set values for what is considered a TAP
    adxl.setTapThreshold(50);           // 62.5 mg per increment
    adxl.setTapDuration(15);            // 625 μs per increment

    // Turning on things
    adxl.ActivityINT(1);
    adxl.singleTapINT(1);

}

void loop() {
  
    // Accelerometer Stuff
    // Accelerometer Axiis
    int x,y,z;   
    adxl.readAccel(&x, &y, &z);
    
    // Print out some stuff
    Serial.println("Axis data: (x,y,z)");
    Serial.print((x+5)/3.5);
    Serial.print(", " );
    Serial.print((y+2)/3.9);
    Serial.print(", ");
    Serial.print((z-116)/4.3); 
    Serial.print(", ");
    Serial.println();

    // Ultrasonic Sensor Stuff
    Serial.println(ultrasonic.distanceRead(INC));

    // Flex Sensor Stuff
    int flexposition;
    // Reads the position of the sensor
    flexposition = analogRead(flexpin);
    // Prints the position of the sensor
    Serial.println("Flex Position: ");
    //Serial.print(flexposition);
    Serial.println();

    delay(1000);
    
}

void writeData(a,b,c) {
  
}

}


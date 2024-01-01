/**
 * TCA9548 I2CScanner.ino -- I2C bus scanner for Arduino
 *
 * Based on https://playground.arduino.cc/Main/I2cScanner/
 *
 */

#include "Wire.h"
#include "SparkFunISL29125.h"

// Declare sensor object
SFE_ISL29125 RGB_sensor1 = SFE_ISL29125(68);

#define TCAADDR 0x70

void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}


// standard Arduino setup()
void setup()
{


  
    while (!Serial);
    delay(1000);

    Wire.begin();
    
    Serial.begin(115200);
    Serial.println("\nTCAScanner new ready!");


  // Initialize the ISL29125 with simple configuration so it starts sampling
    tcaselect(1);
    if (RGB_sensor1.init())
    {
      Serial.println("Sensor Initialization Successful\n\r");
    } else {
      Serial.println("Sensor Initialization Failed\n\r");           
    }
    
    //for (uint8_t t=0; t<8; t++) {
      //tcaselect(t);
      //Serial.print("TCA Port #"); Serial.println(t);

      //for (uint8_t addr = 0; addr<=127; addr++) {
        //if (addr == TCAADDR) continue;

        //Wire.beginTransmission(addr);
        //uint8_t wireRetVal = Wire.endTransmission();
        // Serial.print("endTranismission: ");  
        // Serial.print(addr, DEC);
        // Serial.print(": ");
        //Serial.println(wireRetVal, DEC);
        
        //if (wireRetVal == 0) {
          //Serial.print("Found I2C 0x");  
          //Serial.println(addr,DEC);
        //}
      //}
    //}
    //Serial.println("\ndone");
}

void loop() 
{
}

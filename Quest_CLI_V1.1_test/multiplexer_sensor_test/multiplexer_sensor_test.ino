#include <SparkFunISL29125.h>

/**
 * TCA9548 I2CScanner.ino -- I2C bus scanner for Arduino
 *
 * Based on https://playground.arduino.cc/Main/I2cScanner/
 *
 */

#include "Wire.h"

// Declare sensor object
SFE_ISL29125 RGB_sensor0;
SFE_ISL29125 RGB_sensor1;

// = SFE_ISL29125(68);

#define TCAADDR 0x70

#define IO7 (13)              // Input/Output to payload plus 
#define IO6 (12)              // Input/Output to payload plus 
#define IO5 (11)              // Input/Output to payload plus
#define IO4 (10)              // Input/Output to payload plus
#define IO3 (9)               // Input/Output to payload plus
#define IO2 (4)               // Input/Output to payload plus
#define IO1 (3)               // Input/Output to payload plus
#define IO0 (A6)              // Input/Output to payload plus

uint8_t bus = 4;

void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}


// standard Arduino setup()
void setup()
{ 
  pinMode(IO1, OUTPUT);  //
  pinMode(IO2, OUTPUT);  //
  pinMode(IO3, OUTPUT); //
  pinMode(IO4, OUTPUT); //
  pinMode(IO5, OUTPUT); // 
  pinMode(IO6, OUTPUT); // 
  pinMode(IO7, OUTPUT); // 
  
    while (!Serial);
    delay(1000);

    Wire.begin();
    Serial.begin(115200);
    Serial.println("\nTCAScanner new ready!");

  digitalWrite(IO1, HIGH); // half of pump 1
  digitalWrite(IO2, HIGH); // half of pump 1
  digitalWrite(IO3, HIGH); // half of pump 2 low - on
  digitalWrite(IO4, HIGH); // half of pump 2 low - on
  digitalWrite(IO5, LOW); // oscillater (low is off)
  digitalWrite(IO6, HIGH); // BLUE leds
  digitalWrite(IO7, HIGH); // WHITE leds
  
  // Initialize the ISL29125 with simple configuration so it starts sampling
    tcaselect(bus);
    uint8_t retVal = RGB_sensor0.init();
    Serial.print("Return value: ");
    Serial.println(retVal);
    if (!retVal)
    {
      Serial.println("Sensor 1 Initialization Failed\n\r");
    } else {
      Serial.println("Sensor 1 Initialization Successful\n\r");      
    }
    
    
//    tcaselect(1);
//    if (!RGB_sensor0.init())
//    {
//      Serial.println("Sensor 0 Initialization Failed\n\r");
//    } else {
//      Serial.println("Sensor 0 Initialization Successful\n\r");      
//    }
//    

//    tcaselect(1);
//    if (RGB_sensor1.init())
//    {
//      Serial.println("Sensor 1 Initialization Successful\n\r");
//    } else {
//      Serial.println("Sensor 1 Initialization Failed\n\r");           
//    }

//    for (uint8_t t=0; t<8; t++) {
//      tcaselect(t);
//      Serial.print("TCA Port #"); Serial.println(t);
//
//      for (uint8_t addr = 0; addr<=127; addr++) {
//        if (addr == TCAADDR) continue;
//
//        Wire.beginTransmission(addr);
//        uint8_t wireRetVal = Wire.endTransmission();
//         Serial.print("endTranismission: ");  
//         Serial.print(addr, DEC);
//         Serial.print(": ");
//        Serial.println(wireRetVal, DEC);
//        
//        if (wireRetVal == 0) {
//          Serial.print("Found I2C 0x");  
//          Serial.println(addr,DEC);
//        }
//      }
//    }
    Serial.println("\ndone");
}

void loop() 
{
       // Read sensor values (16 bit integers)
//      tcaselect(0);
//      
//      unsigned int red0 = RGB_sensor0.readRed();
//      unsigned int green0 = RGB_sensor0.readGreen();
//      unsigned int blue0 = RGB_sensor0.readBlue();
//
// 
//      Serial.print("Red0: "); Serial.println(red0,DEC);
//      Serial.print("Green0: "); Serial.println(green0,DEC);
//      Serial.print("Blue0: "); Serial.println(blue0,DEC);
//      Serial.println();
//      
//      delay(2000);      

//      tcaselect(2);
//      
//      unsigned int red1 = RGB_sensor1.readRed();
//      unsigned int green1 = RGB_sensor1.readGreen();
//      unsigned int blue1 = RGB_sensor1.readBlue();
//
// 
//      Serial.print("Red1: "); Serial.println(red1,DEC);
//      Serial.print("Green1: "); Serial.println(green1,DEC);
//      Serial.print("Blue1: "); Serial.println(blue1,DEC);
//      Serial.println();
//      delay(2000);      

}

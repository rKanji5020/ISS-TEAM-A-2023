/**
 * TCA9548 I2CScanner.ino -- I2C bus scanner for Arduino
 *
 * Based on https://playground.arduino.cc/Main/I2cScanner/
 *
 */

#include "Wire.h"

#define TCAADDR 0x70

#define IO7 (13)              // Input/Output to payload plus 
#define IO6 (12)              // Input/Output to payload plus 
#define IO5 (11)              // Input/Output to payload plus
#define IO4 (10)              // Input/Output to payload plus
#define IO3 (9)               // Input/Output to payload plus
#define IO2 (4)               // Input/Output to payload plus
#define IO1 (3)               // Input/Output to payload plus
#define IO0 (A6)              // Input/Output to payload plus

void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}


// standard Arduino setup()
void setup()
{
      // put your setup code here, to run once:
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
    Serial.println("\nTCAScanner ready!");
    
  digitalWrite(IO1, HIGH); // half of pump 1
  digitalWrite(IO2, HIGH); // half of pump 1
  digitalWrite(IO3, HIGH); // half of pump 2 low - on
  digitalWrite(IO4, HIGH); // half of pump 2 low - on
  digitalWrite(IO5, LOW); // oscillater (low is off)
  digitalWrite(IO6, HIGH); // BLUE leds
  digitalWrite(IO7, HIGH); // WHITE leds

  delay(2000);
    for (uint8_t t=0; t<8; t++) {
      tcaselect(t);
      Serial.print("TCA Port #"); Serial.println(t);

      for (uint8_t addr = 0; addr<=127; addr++) {
        if (addr == TCAADDR) continue;

        Wire.beginTransmission(addr);
        if (!Wire.endTransmission()) {
          Serial.print("Found I2C 0x");  Serial.println(addr,HEX);
        }
      }
    }
    Serial.println("\ndone");
}

void loop() 
{
}

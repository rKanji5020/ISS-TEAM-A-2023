
#define IO7 (13)              // Input/Output to payload plus 
#define IO6 (12)              // Input/Output to payload plus 
#define IO5 (11)              // Input/Output to payload plus
#define IO4 (10)              // Input/Output to payload plus
#define IO3 (9)               // Input/Output to payload plus
#define IO2 (2)               // Input/Output to payload plus
#define IO1 (3)               // Input/Output to payload plus
#define IO0 (A6)              // Input/Output to payload plus

void setup() {
  // put your setup code here, to run once:
  pinMode(IO1, OUTPUT);  //nutrient pump (DO1)
  pinMode(IO2, OUTPUT);  //antibiotic pump (DO0)
  //camera leds
  pinMode(IO5, OUTPUT); // BLUE LED pin3
  pinMode(IO4, OUTPUT); // WHITE 1 LED (DO4) 
  pinMode(IO3, OUTPUT); // WHITE 2 LED (DO4) 

  Serial.begin(115200);
}

void loop() {
  // pump 1 runs at full power when IO0 high IO1 low 
  // does not turn off 
  // connection could be weak
  // IO2 does not affect pump 1
  // voltage runs from pump to ground when everything set to high
  // yellow wire on white led seems to not be connected to anything
  // white and blue leds both turn off when IO7 is set to high
  // white leds not affected by IO6

  digitalWrite(IO0, LOW); // half of pump 1
  digitalWrite(IO1, HIGH); // half of pump 1
  digitalWrite(IO2, HIGH); // ??
  digitalWrite(IO3, LOW); // half of pump 2
  digitalWrite(IO4, LOW); // half of pump 2
  digitalWrite(IO5, HIGH); // ??
  digitalWrite(IO6, LOW); // white and blue leds
  digitalWrite(IO7, LOW); // ALSO white and blue leds

  // delay(2000);
  // digitalWrite(IO1, LOW);
  //digitalWrite(IO2, LOW);

  // delay(2000);
  // digitalWrite(IO1, HIGH);
  //digitalWrite(IO2, HIGH);

  //delay(2000);
  //digitalWrite(IO5, LOW);
  //digitalWrite(IO6, LOW);

  //delay(2000);
  //digitalWrite(IO5, HIGH);
  //digitalWrite(IO6, HIGH);
  
}

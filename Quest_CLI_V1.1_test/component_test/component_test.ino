
#define IO7 (13)              // Input/Output to payload plus 
#define IO6 (12)              // Input/Output to payload plus 
#define IO5 (11)              // Input/Output to payload plus
#define IO4 (10)              // Input/Output to payload plus
#define IO3 (9)               // Input/Output to payload plus
#define IO2 (4)               // Input/Output to payload plus
#define IO1 (3)               // Input/Output to payload plus
#define IO0 (A6)              // Input/Output to payload plus

void setup() {
  // put your setup code here, to run once:
  pinMode(IO1, OUTPUT);  //
  pinMode(IO2, OUTPUT);  //
  pinMode(IO3, OUTPUT); //
  pinMode(IO4, OUTPUT); //
  pinMode(IO5, OUTPUT); // 
  pinMode(IO6, OUTPUT); // 
  pinMode(IO7, OUTPUT); // 
  //camera leds



  Serial.begin(115200);
}

void loop() {

  //old
  // pump 1 runs at full power when IO0 high IO1 low 
  // does not turn off 
  // connection could be weak
  // IO2 does not affect pump 1
  // voltage runs from pump to ground when everything set to high
  // yellow wire on white led seems to not be connected to anything
  // white and blue leds both turn off when IO7 is set to high
  // white leds not affected by IO6

  //new
  //IO4 IO5 low for full power left pump

  digitalWrite(IO1, HIGH); // half of pump 1
  digitalWrite(IO2, HIGH); // half of pump 1
  digitalWrite(IO3, HIGH); // half of pump 2 low - on
  digitalWrite(IO4, HIGH); // half of pump 2 low - on
  digitalWrite(IO5, LOW); // oscillater (low is off)
  digitalWrite(IO6, HIGH); // BLUE leds
  digitalWrite(IO7, HIGH); // WHITE leds

  delay(2000);
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

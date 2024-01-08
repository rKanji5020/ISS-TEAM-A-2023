
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
  // put your main code here, to run repeatedly:

  digitalWrite(IO1, HIGH); // Nutrient pump off
  digitalWrite(IO2, HIGH); //antiboitc pump off
  digitalWrite(IO5, HIGH); // Blue LED off
  digitalWrite(IO4, HIGH); // WHITE 1 off
  digitalWrite(IO3, HIGH); // WHITE 2 off

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

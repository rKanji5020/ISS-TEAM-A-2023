
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
  pinMode(IO1, OUTPUT);  //nutrient pump pin1
  pinMode(IO2, OUTPUT);  //antibiotic pump pin2
  //camera leds
  pinMode(IO5, OUTPUT); // WHITE LED pin3
  pinMode(IO6, OUTPUT); // BLUE LED 2 pin4
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(IO1, HIGH);
  digitalWrite(IO2, HIGH);
  digitalWrite(IO5, HIGH);
  digitalWrite(IO6, HIGH);

  delay(2000);
  digitalWrite(IO1, LOW);
  //digitalWrite(IO2, LOW);

  delay(2000);
  digitalWrite(IO1, HIGH);
  //digitalWrite(IO2, HIGH);

  //delay(2000);
  //digitalWrite(IO5, LOW);
  //digitalWrite(IO6, LOW);

  //delay(2000);
  //digitalWrite(IO5, HIGH);
  //digitalWrite(IO6, HIGH);
  
}

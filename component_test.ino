void setup() {
  // put your setup code here, to run once:
  pinMode(0, OUTPUT);  //nutrient pump pin1
  pinMode(1, OUTPUT);  //antibiotic pump pin2
  //camera leds
  pinMode(4, OUTPUT); // WHITE LED pin3
  pinMode(5, OUTPUT); // BLUE LED 2 pin4
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(0, HIGH);
  digitalWrite(1, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);

  delay(5000);
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);

  delay(5000);
  digitalWrite(0, HIGH);
  digitalWrite(1, HIGH);

  delay(5000);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);

  delay(5000);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  
}

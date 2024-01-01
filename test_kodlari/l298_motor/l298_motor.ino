
const int motorKontrolKartipwmpin = 3;
const int motor1pinbir =8;
const int motor1piniki = 9;
void setup() {
  // put your setup code here, to run once:
  //pinmode tanımlamaları
  pinMode(motor1pinbir,OUTPUT);
  pinMode(motor1piniki,OUTPUT);
  pinMode(motorKontrolKartipwmpin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(motorKontrolKartipwmpin,30);
  digitalWrite(motor1pinbir,HIGH);
  digitalWrite(motor1piniki,HIGH);
  delay(5000);
}

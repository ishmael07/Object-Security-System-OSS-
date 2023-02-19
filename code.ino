#include <LiquidCrystal.h>
#define LED_PIN_BLUE 10
#define LED_PIN_RED 9


const int trigPin = 11;
const int echoPin = 12; 
const int buzzerPin = 8;
int fsrAnalogPin = 0; 
int fsrReading;
String input;
String pin = "0712";


long duration;
int distanceCm, distanceInch;

LiquidCrystal lcd(2,3,4,5,6,7);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  pinMode(LED_PIN_BLUE, OUTPUT);
  pinMode(LED_PIN_RED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
  lcd.setCursor(0,0);
  lcd.print("Please Enter Pin!");
  Serial.println("Please Enter Your Pin.");
  delay(5000);

}

void loop() {


  String input = Serial.readString();

  if (input == "0712\n") {
    Serial.print("Correct");
    lcd.print("Correct!");
  } else {
    Serial.print("Incorrect");
 }

lcd.clear();

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034/2;
  distanceInch = duration * 0.0133 / 2;
  delay(10);
  


  lcd.setCursor(0,1);
  lcd.print("Distance: ");
  lcd.print(distanceInch);
  lcd.print(" inch");
  delay(250);
 
  if (distanceInch < 10) {
    lcd.setCursor(0,0);
    lcd.print("DO NOT TOUCH!");
    digitalWrite(LED_PIN_BLUE, HIGH); 
    delay(25);
    digitalWrite(LED_PIN_BLUE, LOW);
    delay(25);
    digitalWrite(LED_PIN_RED, HIGH);
    delay(25);
    digitalWrite(LED_PIN_RED, LOW);
    delay(25);
  }else if (distanceInch < 15) {
    lcd.clear();
    lcd.print("WARNING!");
    digitalWrite(LED_PIN_BLUE, HIGH); 
    delay(50);
    digitalWrite(LED_PIN_BLUE, LOW);
    delay(50);
    digitalWrite(LED_PIN_RED, HIGH);
    delay(50);
    digitalWrite(LED_PIN_RED, LOW);
    delay(50);
    
  }else {
    lcd.setCursor(0,0);
    lcd.print("Object is Safe");
  }

  fsrReading = analogRead(fsrAnalogPin);
 

  if (fsrReading >= 121) {
    digitalWrite(buzzerPin, LOW);
  } else if (fsrReading < 120) {
    digitalWrite(buzzerPin, HIGH);
    Serial.print("OBJECT STOLEN! Person Notified.");
    Serial.println(" ");
    lcd.setCursor(0,0);
    lcd.print("ALARM ACTIVATED");
     digitalWrite(LED_PIN_BLUE, HIGH); 
    delay(10);
    digitalWrite(LED_PIN_BLUE, LOW);
    delay(10);
    digitalWrite(LED_PIN_RED, HIGH);
    delay(10);
    digitalWrite(LED_PIN_RED, LOW);
    delay(10);

  }

}

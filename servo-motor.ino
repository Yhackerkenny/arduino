#include <Servo.h>

Servo myservo;

const int trigPin = 9;
const int echoPin = 10;

void setup() {
  myservo.attach(6);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.print(distance);
  Serial.println("cm");
  if (distance < 100) {
    myservo.write(190);
    delay(1000);
  }
  else {
    myservo.write(0);
  }
}

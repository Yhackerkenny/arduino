
#include <SoftwareSerial.h>

//defining the pins
SoftwareSerial BTserial(10, 11); // RX | TX
const int trigPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 8; // Echo Pin of Ultrasonic Sensor
const int laser = 9; // laser pin
const int buzzer = 6;// buzzer pin
const int ldrPin = A0;// ldr pin
//distances
const int DISTANCE_THRESHOLD = 10; //distance to turn buzzer on if it passes..
int percentage,x,per;

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
   BTserial.begin(9600);// starting bluetooth terminal 
   pinMode(laser,OUTPUT);
   pinMode(buzzer,OUTPUT);
   pinMode(ldrPin, INPUT);
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);
}

void loop() {
 digitalWrite(laser,HIGH);// turn on laser..
 int ldrValue = analogRead(ldrPin);
 
  long duration, inches, cm;
   digitalWrite(trigPin, LOW);
   delayMicroseconds(2);
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);
   
   duration = pulseIn(echoPin, HIGH);
   cm = microsecondsToCentimeters(duration);
  
    if (cm ==48){
    x = 48;
   }
   else if (cm ==49){
    x = 49;
   } 
   else if (cm ==50){
    x = 50;
   }
  else if (cm ==51){
    x = 51;
   }
   else if (cm ==49){
    x = 49;
   }
  
   else if (cm ==52){
    x = 52;
   }
   else if (cm <0){
    BTserial.print("  THE DUSTBIN IS OPENED  ");
   }
   else if (cm >52){
    BTserial.print("  THE DUSTBIN IS OPENED  ");
   }
   else{
   }
   percentage = (cm*100)/x;
   per = 100 - percentage;

 while (BTserial.available()) {
    char command = BTserial.read();
    Serial.println(command);
    switch (command) {
      case 'STOP':
        stop(); // call the stop() function when 'STOP' is received
        break;
      case 'D2':
        delay2();
        break;
      case 'D3':
        delay3();
        break;
      case 'D4':
        delay3();
        break;
    }
  }
  

//   //printing
//    Serial.print("ldrvalue : ");
//    Serial.print(ldrValue);
//    Serial.print("   //  ");
//    BTserial.print("ldrvalue : ");
//    BTserial.print(ldrValue);
//    BTserial.print("  //  ");
//    Serial.print("centimeters : ");
//    Serial.print(cm);
//    Serial.print("   //  ");
    Serial.print("percentage : ");
    Serial.print(per);
    Serial.print(" %");
    
    BTserial.print("percentage : ");
    BTserial.print(per);
    BTserial.print(" %");
   Serial.println();
   BTserial.println();
   delay(1000);
   //tone(buzzer,2000);

if(cm < DISTANCE_THRESHOLD and ldrValue < 200 ) {
  full();
  }  
else {
  BTserial.println("EMPTY");
  Serial.println("EMPTY");
  noTone(buzzer);
}  
}
long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}


void full(){
      
    tone(buzzer,2000);
    BTserial.println("    STREAT A   ");
    BTserial.println("FULL");
    Serial.println("FULL");
}
void stop() {
  noTone(buzzer); // stop the buzzer
  Serial.println("FULL"); // print "FULL" to the serial terminal
  BTserial.println("FULL"); // print "FULL" to the Bluetooth terminal
}

void delay2() {
noTone(buzzer);
delay(2000);
full();
}
void delay3() {
noTone(buzzer);
delay(3000);
full();
}
void delay4() {
noTone(buzzer);
delay(4000);
full();
}

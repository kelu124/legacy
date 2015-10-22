#include <Servo.h>
 
Servo myservo;  // create servo object to control a servo

int pos = 90;    // variable to store the servo position
int pinPulse = 13;
int deb;
int fin;
int t;
int tempo=2;
int ntire=1500; // nearly 200 us per shoot
int del=198;
int wait=0000;
 
void setup() {
 
 myservo.attach(3);  // attaches the servo on pin 9 to the servo object
 pinMode (pinPulse, OUTPUT);
 Serial.begin(9600);
 
}
 
void loop() {
 
  for (pos = 70; pos <= 130; pos += 1) { // goes from 90 degrees to 180 degrees

  myservo.write(pos);              // tell servo to go to position in variable 'pos'
  delay(10);               // waits 5ms for the servo to reach the position

  for (int i=0 ; i<ntire ; i+=1) {
    REG_PIOB_SODR = 0x1 << 27;
    t=0;
    while (t<tempo){
      REG_PIOB_SODR = 0x1 << 27;
      t++;
      }
    REG_PIOB_CODR = 0x1 << 27;
    delayMicroseconds(del);
    }
    delay(wait);
  }
 
  
 for (pos = 130; pos >= 70; pos -= 1) { // goes from 180 degrees to 0 degrees\
 
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
  delay(10);               // waits 5ms for the servo to reach the position

  for (int i=0 ; i<ntire ; i+=1) {
    REG_PIOB_SODR = 0x1 << 27;
    t=0;
    while (t<tempo){
      REG_PIOB_SODR = 0x1 << 27;
      t++;
      }
    REG_PIOB_CODR = 0x1 << 27;
    delayMicroseconds(del);
    }
    delay(wait);
  }
 }

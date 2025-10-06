/*
 */
#include <Servo.h> // Include the Servo library

Servo myservo;  // Create a servo object to control a servo.

int potpin = 2; //

void setup() {
   myservo.attach(2); 
}

void loop() {
      // Example: Sweep from 0 to 180 degrees
  for (int pos = 0; pos <= 180; pos += 1) {
    myservo.write(pos); // tell servo to go to position in variable 'pos'
    delay(15); // waits for the servo to reach the position
  }
  for (int pos = 180; pos >= 180; pos -= 1) {
    myservo.write(pos); // tell servo to go to position in variable 'pos'
    delay(15); // waits for the servo to reach the position
  }
}

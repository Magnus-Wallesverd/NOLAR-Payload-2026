/*
Input1	Input2	Spinning Direction
Low(0)	Low(0)	Motor OFF
High(1)	Low(0)	Forward
Low(0)	High(1)	Backward
High(1)	High(1)	Motor OFF

https://lastminuteengineers.com/l298n-dc-stepper-driver-arduino-tutorial/ - source

 */



int motorPin1 = 2; 
int motorPin2 = 3; 
void setup() {
  pinMode(motorPin1, OUTPUT); // Set the motor pin as an output
  pinMode(motorPin2, OUTPUT); // Set the motor pin as an output
}

void loop() {
  digitalWrite(motorPin1, HIGH); // Turn the motor ON (full speed)
  delay(1000); // Wait for 3 seconds
  digitalWrite(motorPin2, LOW);  // Turn the motor OFF
  delay(1000); // Wait for 3 seconds
}

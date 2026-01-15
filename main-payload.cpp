// Soil Sensor Imports
#include <AltSoftSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//gps imports
#include <SoftwareSerial.h>
#include <TinyGPS++.h>


// Soil Sensor
// RO to pin 8 & DI to pin 9 when using AltSoftSerial
#define RE 6
#define DE 7

//soil sensor
const byte nitro[] = {0x01, 0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte phos[] = {0x01, 0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte pota[] = {0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};
const byte npk[] = {0x01, 0x03, 0x00, 0x1e, 0x00, 0x03, 0x65, 0xcd};
const byte cond[] = {0x01, 0x03, 0x00, 0x15, 0x00, 0x01, 0x95, 0xCE};
const byte ph[] = {0x01, 0x03, 0x00, 0x06, 0x00, 0x01, 0x64, 0x0B};

byte values[11];
AltSoftSerial mod;

//gps 
static const int RXPin = 3, TXPin = 2; // Example pins
static const uint32_t GPSBaud = 9600;

SoftwareSerial gpsSerial(TXPin, RXPin); 
TinyGPSPlus gps;

// dc motor 1
int motorPin1 = 2; 
int motorPin2 = 3; 

//dc motor 2
int motorPin1 = 2; 
int motorPin2 = 3; 

// dc motor 3
int motorPin1 = 2; 
int motorPin2 = 3; 

//dc motor 4
int motorPin1 = 2; 
int motorPin2 = 3; 


void setup() {
  Serial.begin(9600);

  //soil sensor begin
  mod.begin(9600);
  //gps instance begin
  gpsSerial.begin(9600);
  Serial.println("GPS Start")

  // soil sensor
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  // dc motor 1
  pinMode(motorPin1, OUTPUT); // Set the motor pin as an output
  pinMode(motorPin2, OUTPUT); // Set the motor pin as an output
  // dc motor 2
  pinMode(motorPin1, OUTPUT); // Set the motor pin as an output
  pinMode(motorPin2, OUTPUT); // Set the motor pin as an output
  // dc motor 3
  pinMode(motorPin1, OUTPUT); // Set the motor pin as an output
  pinMode(motorPin2, OUTPUT); // Set the motor pin as an output
  // dc motor 4
  pinMode(motorPin1, OUTPUT); // Set the motor pin as an output
  pinMode(motorPin2, OUTPUT); // Set the motor pin as an output

  // soil sensor
  // put RS-485 into receive mode
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
  // soil sensor end

}

void loop() {

// soil sensor
  byte val1, val2, val3, val4, val5;
  Serial.print("Nitrogen: ");
  val1 = nitrogen();
  Serial.print(" = ");
  Serial.print(val1);
  Serial.println(" mg/kg");
  delay(250);

  Serial.print("Phosphorous: ");
  val2 = phosphorous();
  Serial.print(" = ");
  Serial.print(val2);
  Serial.println(" mg/kg");
  delay(250);

  Serial.print("Potassium: ");
  val3 = potassium();
  Serial.print(" = ");
  Serial.print(val3);
  Serial.println(" mg/kg");
  
  Serial.print("Conductivity: ");
  val4 = soilconductivity();
  Serial.print(" = ");
  Serial.print(val4);
  Serial.println(" uS/cm");
  
  Serial.print("pH: ");
  val3 = potassium();
  Serial.print(" = ");
  Serial.print(val5);
  Serial.println(" pH");
  Serial.println();
  Serial.println();

  delay(1000);
  //soil sensor end

  // dc motors 'if' placeholder
  if() {
    //dc motor 1
    digitalWrite(motorPin1, HIGH); // Turn the motor ON (full speed)
    delay(1000); // Wait for 3 seconds
    digitalWrite(motorPin2, LOW);  // Turn the motor OFF
    delay(1000); // Wait for 3 seconds
    //dc motor 2
    digitalWrite(motorPin1, HIGH); // Turn the motor ON (full speed)
    delay(1000); // Wait for 3 seconds
    digitalWrite(motorPin2, LOW);  // Turn the motor OFF
    delay(1000); // Wait for 3 seconds
    //dc motor 3
    digitalWrite(motorPin1, HIGH); // Turn the motor ON (full speed)
    delay(1000); // Wait for 3 seconds
    digitalWrite(motorPin2, LOW);  // Turn the motor OFF
    delay(1000); // Wait for 3 seconds
    //dc motor 4
    digitalWrite(motorPin1, HIGH); // Turn the motor ON (full speed)
    delay(1000); // Wait for 3 seconds
    digitalWrite(motorPin2, LOW);  // Turn the motor OFF
    delay(1000); // Wait for 3 seconds
  }

  // gps
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read())
    }
        // Data successfully parsed, now you can access GPS information
        if (gps.location.isUpdated()) {
        Serial.print("Satellite Count:");
        Serial.println(gps.satellites.values(), 6);
        Serial.print("Latitude: ");
        Serial.println(gps.location.lat(), 6);
        Serial.print("Longitude: ");
        Serial.println(gps.location.lng(), 6);
        // ... and other data like altitude, speed, date, time

        Serial.print("Altitude Feet:");
        Serial.println(gps.altitude.feet());
        Serial.println("");

        } else {
        Serial.println("Location Invalid");
        }   
    //gps end
}

// soil sensor
byte nitrogen() {
  // clear the receive buffer
  mod.flushInput();

  // switch RS-485 to transmit mode
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(1);

  // write out the message
  for (uint8_t i = 0; i < sizeof(nitro); i++ ) mod.write( nitro[i] );

  // wait for the transmission to complete
  mod.flush();
  
  // switching RS485 to receive mode
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);

  // delay to allow response bytes to be received!
  delay(200);

  // read in the received bytes
  for (byte i = 0; i < 7; i++) {
    values[i] = mod.read();
    Serial.print(values[i], HEX);
    Serial.print(' ');
  }
  return values[4];
}

byte phosphorous() {
  mod.flushInput();
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(1);
  for (uint8_t i = 0; i < sizeof(phos); i++ ) mod.write( phos[i] );
  mod.flush();
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
// delay to allow response bytes to be received!
  delay(200);
  for (byte i = 0; i < 7; i++) {
    values[i] = mod.read();
    Serial.print(values[i], HEX);
    Serial.print(' ');
  }
  return values[4];
}

byte potassium() {
  mod.flushInput();
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(1);
  for (uint8_t i = 0; i < sizeof(pota); i++ ) mod.write( pota[i] );
  mod.flush();
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
// delay to allow response bytes to be received!
  delay(200);
  for (byte i = 0; i < 7; i++) {
    values[i] = mod.read();
    Serial.print(values[i], HEX);
    Serial.print(' ');
  }
  return values[4];
}

// register with all npk vals
  byte* npkall() {
    byte arr[3];
    mod.flushInput();
    digitalWrite(DE, HIGH);
    digitalWrite(RE, HIGH);
    delay(1);
    for (uint8_t i = 0; i < sizeof(pota); i++ ) mod.write( npk[i] );
    mod.flush();
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);

    delay(200);
    for (byte i = 0; i < 7; i++) {
    values[i] = mod.read();
    Serial.print(values[i], HEX);
    Serial.print(' ');
    }
    arr[0] = values[4];
    arr[1] = values[6];
    arr[2] = values[8];

    return arr;
  }

  byte soilconductivity(){
    mod.flushInput();
    digitalWrite(DE, HIGH);
    digitalWrite(RE, HIGH);
    delay(1);
    for (uint8_t i = 0; i < sizeof(cond); i++ ) mod.write( cond[i] );
    mod.flush();
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
    // delay to allow response bytes to be received!
    delay(200);
    for (byte i = 0; i < 7; i++) {
      values[i] = mod.read();
      Serial.print(values[i], HEX);
      Serial.print(' ');
    }
    return values[4];
  }

  byte pHlevel(){
    mod.flushInput();
    digitalWrite(DE, HIGH);
    digitalWrite(RE, HIGH);
    delay(1);
    for (uint8_t i = 0; i < sizeof(ph); i++ ) mod.write( ph[i] );
    mod.flush();
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
// delay to allow response bytes to be received!
    delay(200);
    for (byte i = 0; i < 7; i++) {
      values[i] = mod.read();
      Serial.print(values[i], HEX);
      Serial.print(' ');
    }
    return values[4];
  }
//soil sensor end


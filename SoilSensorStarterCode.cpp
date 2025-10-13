/*
 * https://www.circuitschools.com/
 * Interfacing Soil NPK Sensor with Arduino for measuring 
 * Nitrogen, Phosphorus, and Potassium nutrients
 */

#include <AltSoftSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//#define SCREEN_WIDTH 128    // OLED display width, in pixels
//#define SCREEN_HEIGHT 64    // OLED display height, in pixels
//#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// RO to pin 8 & DI to pin 9 when using AltSoftSerial
#define RE 6
#define DE 7

const byte nitro[] = {0x01, 0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte phos[] = {0x01, 0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte pota[] = {0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};
const byte npk[] = {0x01, 0x03, 0x00, 0x1e, 0x00, 0x03, 0x65, 0xcd};
const byte cond[] = {0x01, 0x03, 0x00, 0x15, 0x00, 0x01, 0x95, 0xCE};
const byte ph[] = {0x01, 0x03, 0x00, 0x06, 0x00, 0x01, 0x64, 0x0B};

byte values[11];
AltSoftSerial mod;


void setup() {
  Serial.begin(9600);
  mod.begin(9600);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);

  // put RS-485 into receive mode
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);

  /*
  //Initializing and Configuring OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  delay(500);
  display.clearDisplay();
  display.setCursor(25, 15);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Soil NPK Sensor");
  display.setCursor(25, 35);
  display.setTextSize(1);
  display.print("Initializing");
  display.display();
  delay(3000);
  */
}

void loop() {

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

/*
display.clearDisplay();
   
  display.setTextSize(2);
  display.setCursor(0, 5);
  display.print("N: ");
  display.print(val1);
  display.setTextSize(1);
  display.print(" mg/kg");
 
  display.setTextSize(2);
  display.setCursor(0, 25);
  display.print("P: ");
  display.print(val2);
  display.setTextSize(1);
  display.print(" mg/kg");
 
  display.setTextSize(2);
  display.setCursor(0, 45);
  display.print("K: ");
  display.print(val3);
  display.setTextSize(1);
  display.print(" mg/kg");
  display.display();
  
*/
delay(1000);
}

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


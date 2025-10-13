#include <SoftwareSerial.h>
#include <TinyGPS++.h>

static const int RXPin = 3, TXPin = 2;
static const uint32_t GPSBaud = 9600;

SoftwareSerial gpsSerial(TXPin, RXPin); // Note: RXPin is connected to GPS TX, TXPin to GPS RX
TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(GPSBaud);

  Serial.println("GPS Debugging Started");
  Serial.print("Testing TinyGPS++ library v. ");
  Serial.println(TinyGPSPlus::libraryVersion());
}

void loop() {
  // This sketch pretty much follows the "Device Example" from the TinyGPS++ library.
  while (gpsSerial.available() > 0) {
    char c = gpsSerial.read(); // Read one character
    Serial.write(c); // Echo it to the Serial Monitor for debugging
    if (gps.encode(c)) { // Try to encode the completed data
      displayInfo(); // If new data is fully encoded, display it
    }
  }

  // If no data is received for 5 seconds, print a warning
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println("WARNING: No GPS data received. Check wiring and baud rate.");
    while(true); // Stop the sketch
  }
}

void displayInfo() {
  if (gps.location.isValid()) {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Satellites in use: ");
    Serial.println(gps.satellites.value());
  } else {
    Serial.println("Location Invalid");
  }
}
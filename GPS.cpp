  // https://www.youtube.com/watch?v=hB8q2ASHhjY
  
  #include <SoftwareSerial.h>
  #include <TinyGPS++.h>


    static const int RXPin = 3, TXPin = 2; // Example pins
    static const uint32_t GPSBaud = 9600;


  SoftwareSerial gpsSerial(TXPin, RXPin);
  TinyGPSPlus gps;

  void setup() {
      Serial.begin(9600); // For debugging output
      gpsSerial.begin(9600);
  }

    void loop() {
      while (gpsSerial.available() > 0) {
        if (gps.encode(gpsSerial.read())) {
          // Data successfully parsed, now you can access GPS information
          if (gps.location.isValid()) {
            Serial.print("Latitude: ");
            Serial.println(gps.location.lat(), 6);
            Serial.print("Longitude: ");
            Serial.println(gps.location.lng(), 6);
            // ... and other data like altitude, speed, date, time
          } else {
            Serial.println("Location Invalid");
          }
        }
      }
    }
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
      Serial.println("GPS Start")
  }

    void loop() {
      while (gpsSerial.available()) {
        gps.encode(gpsSerial.read())
      }
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
        }
  
    
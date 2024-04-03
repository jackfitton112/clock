#include <clock.h>

/*
Cycling demo between words and date

Note: Doesnt do daylight savings automatically
*/

Clock gpsclock;
TinyGPSPlus gps;

void setup() {
  // put your setup code here, to run once:
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  Serial.begin(115200);

  while(!Serial);

  gpsclock.begin();
  gpsclock.displayOn();
  pinMode(2, OUTPUT);

  //Comment this out to disable daylight savings time (GMT+1)
  gpsclock.EnableDST();



}

int counter = 1;

void updateTimeGPS(){
  int i = 0;
    while (Serial2.available() > 0) { //This is failing.
        int byteRead = Serial2.read();  // Read a byte from the serial


        if (gps.encode(byteRead)) {  // Pass the read byte to the gps.encode() method
            // Get the time from the GPS
            if (gps.time.isValid()) {
                int hour = gps.time.hour();
                int minute = gps.time.minute();
                int second = gps.time.second();
                Serial.print(hour);
                Serial.print(minute);
                Serial.println(second);
                gpsclock.updateTime(hour, minute, second);
                break;
            }
        }
    }

    if (i > 0) {

        digitalWrite(2, LOW);
        Serial.println("Failed to read from GPS");
    }


}

void updateDataGPS(){
    int i = 0;
    while (Serial2.available() > 0) { //This is failing.
        int byteRead = Serial2.read();  // Read a byte from the serial
        //Serial.print(byteRead);  // Print the byte for debugging purposes

        //turn on pin 2 to show that the gps is working
        digitalWrite(2, HIGH);

        if (gps.encode(byteRead)) {  // Pass the read byte to the gps.encode() method
            // Get the time from the GPS
            if (gps.time.isValid()) {
                int day = gps.date.day();
                int month = gps.date.month();
                int year = gps.date.year();

                

                Serial.print(year);

                gpsclock.updateDate(day, month, year);
                break;
            }
        }
    }

    if (i > 0) {
        //turn off pin 2 to show that the gps is not working
        //print failed message
        digitalWrite(2, LOW);
        Serial.println("Failed to read from GPS");
    }
}



void loop() {

  updateDataGPS();

  delay(5000);

  gpsclock.type("YES GPS");

  delay(5000);




}

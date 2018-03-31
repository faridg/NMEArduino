#include <LiquidCrystal.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define GPS_BAUD 9600 
#define ARDUINO_GPS_RX 2 
#define ARDUINO_GPS_TX 3 

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
SoftwareSerial ss(ARDUINO_GPS_TX, ARDUINO_GPS_RX); 
TinyGPSPlus gps; 

void setup()
{
  Serial.begin(9600);
  ss.begin(GPS_BAUD);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("GPS++");
  lcd.setCursor(0,1);
}

void loop()
{
  serialNMEA();
  displayNMEA();
  smartDelay(1000); 
}

void serialNMEA()
{
Serial.print("lat="); Serial.println(gps.location.lat(), 6); 
Serial.print("lng="); Serial.println(gps.location.lng(), 6);
Serial.print("rawLat="); Serial.println(gps.location.rawLat().deg); 
Serial.print("rawLat="); Serial.println(gps.location.rawLat().billionths);
Serial.print("rawLng="); Serial.println(gps.location.rawLng().deg); 
Serial.print("rawLng="); Serial.println(gps.location.rawLng().billionths);
Serial.print("rawDate="); Serial.println(gps.date.value()); 
Serial.print("year="); Serial.println(gps.date.year()); 
Serial.print("month="); Serial.println(gps.date.month()); 
Serial.print("day="); Serial.println(gps.date.day()); 
Serial.print("rawTime="); Serial.println(gps.time.value()); 
Serial.print("hour="); Serial.println(gps.time.hour()); 
Serial.print("minute="); Serial.println(gps.time.minute()); 
Serial.print("second="); Serial.println(gps.time.second()); 
Serial.print("centisecond="); Serial.println(gps.time.centisecond()); 
Serial.print("rawSpeed="); Serial.println(gps.speed.value()); 
Serial.print("knots="); Serial.println(gps.speed.knots()); 
Serial.print("mph"); Serial.println(gps.speed.mph()); 
Serial.print("mps="); Serial.println(gps.speed.mps()); 
Serial.print("kmh="); Serial.println(gps.speed.kmph()); 
Serial.print("rawCourse="); Serial.println(gps.course.value()); 
Serial.print("courseDegree="); Serial.println(gps.course.deg()); 
Serial.print("rawAlt="); Serial.println(gps.altitude.value()); 
Serial.print("meterAlt="); Serial.println(gps.altitude.meters()); 
Serial.print("mileAlt="); Serial.println(gps.altitude.miles()); 
Serial.print("kmAlt="); Serial.println(gps.altitude.kilometers()); 
Serial.print("ftAlt="); Serial.println(gps.altitude.feet()); 
Serial.print("satnum="); Serial.println(gps.satellites.value()); 
Serial.print("pre="); Serial.println(gps.hdop.value()); 
}
void displayNMEA()
{

  int x = analogRead (0);
  lcd.setCursor(0,1);
  if (x < 60) {
    lcd.print (gps.location.lat());
  }
  else if (x < 200) {
    lcd.print (gps.satellites.value());
  }
  else if (x < 400){
    lcd.print (gps.speed.kmph());
  }
  else if (x < 600){
    lcd.print (gps.location.lng());
  }
  else if (x < 800){
    lcd.print ("Select");
  }
}
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

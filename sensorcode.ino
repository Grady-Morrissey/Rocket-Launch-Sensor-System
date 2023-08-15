//written by Grady Morrissey - BIRST RIBS 2023

//Rocket launch sensing system using GY-86 (MS5611 HMC5883L MPU6050), BME280, GY-NEO6MV2 NEO-6M for use with Arduino Uno
//Temperature, Altitude, Compass/Magnetometer, GPS, Pressure, 3D gyroscope, 3D accelerometer, Humidity
//System can be run with an external portable battery. 

//based on
//https://randomnerdtutorials.com/arduino-mpu-6050-accelerometer-gyroscope/
//https://lastminuteengineers.com/ms5611-barometric-pressure-sensor-arduino-tutorial/
//library examples
//https://www.circuitbasics.com/writing-data-to-files-on-an-sd-card-on-arduino/
//https://randomnerdtutorials.com/guide-to-neo-6m-gps-module-with-arduino/

//hardware
//https://www.amazon.com/JESSINIE-GY-86-HMC5883L-Module-Acceleration/dp/B0BG2FTNWY/ref=sr_1_1?crid=WM7TSB9TFT40&keywords=gy86+arduino&qid=1688682414&s=industrial&sprefix=gy86+arduino%2Cindustrial%2C205&sr=1-1
//https://www.amazon.com/HiLetgo-GY-NEO6MV2-Controller-Ceramic-Antenna/dp/B01D1D0F5M/ref=sr_1_1?crid=10W46UCCGJ1LO&keywords=hiletgo+gy-neo6&qid=1688683215&s=industrial&sprefix=hiletgo+gy-neo%2Cindustrial%2C238&sr=1-1
//https://www.amazon.com/KeeYees-Temperature-Humidity-Atmospheric-Barometric/dp/B07KYJNFMD/ref=sr_1_2_sspa?crid=3NRPRC576A33K&keywords=bme280&qid=1692117490&s=industrial&sprefix=bme280%2Cindustrial%2C325&sr=1-2-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1




//////////////////////////////////////////////////////////////////////////////////////initialization

//mpu6050
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
Adafruit_MPU6050 mpu;

////MS5611
//#include "MS5611.h"
//MS5611 MS5611(0x77);  //make sure this doesn't interfere with BME280

//SD card
#include <SPI.h>
#include <SD.h>
const int chipSelect = 4;

//GPS
#include <SoftwareSerial.h>
SoftwareSerial ss(2,3);

//BME
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme; // I2C
unsigned long delayTime;
 

//////////////////////////////////////////////////////////////////////////////////////setup

void setup(void) {
  Serial.begin(9600);  //this can change, maybe to 115200
  while (!Serial) {
    delay(10); // this is meant to pause arduino until serial console opens, I might want to remove this
  }

  //maybe for flight software get rid of these checks in case something unwires during flight, can still get some data (tentative)

  // MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G); //what G range do we need? (I think rocket pulls 3 Gs)
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

//  //MS5611
//  if (!MS5611.begin()) {
//    Serial.println("MS5611 not found, check wiring!");
//    while (1) {
//      delay(10);
//    }
//  }

  //GPS
  ss.begin(9600);

  //BME
  if (! bme.begin(0x76)) {
      Serial.println("Could not find a valid BME280 sensor, check wiring!");
      while (1);
  }
       
  //SD card
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  
  Serial.println("card initialized.");
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  Serial.println("Datalogger restart");
  dataFile.println("Datalogger restart");
  dataFile.close();

  Serial.println("");
  delay(1000);
}

//////////////////////////////////////////////////////////////////////////////////////loop

void loop() {

  //MPU6050
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

//  Serial.print(a.acceleration.x);
//  Serial.print(",");
//  Serial.print(a.acceleration.y);
//  Serial.print(",");
//  Serial.print(a.acceleration.z);
//  Serial.print(",");
//  Serial.print(g.gyro.x);
//  Serial.print(",");
//  Serial.print(g.gyro.y);
//  Serial.print(",");
//  Serial.print(g.gyro.z);
//  Serial.print(",");
  

  //MS5611
//  MS5611.read();
//  Serial.print(MS5611.getTemperature(), 3);
//  Serial.print(MS5611.getPressure(), 3);
//  Serial.println();

  //BME

  //SD Card
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {

    Serial.print("Sensors:\n");
    Serial.print(a.acceleration.x);
    Serial.print(",");
    Serial.print(a.acceleration.y);
    Serial.print(",");
    Serial.print(a.acceleration.z);
    Serial.print(",");
    Serial.print(g.gyro.x);
    Serial.print(",");
    Serial.print(g.gyro.y);
    Serial.print(",");
    Serial.print(g.gyro.z);
    Serial.print(",");

//    Serial.print(MS5611.getTemperature(), 3);
//    Serial.print(",");
//    Serial.print(MS5611.getPressure(), 3);
//    Serial.print(",");

    Serial.print(bme.readTemperature());
    Serial.print(",");
    Serial.print(bme.readPressure() / 100.0F);
    Serial.print(",");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.print(",");
    Serial.print(bme.readHumidity());
    Serial.print(",");

    Serial.print("\n");
    
    Serial.print("GPS:\n");

    /////////////////////////////////////////////////save to SD
    dataFile.print("Sensors:\n");
    dataFile.print(a.acceleration.x);
    dataFile.print(",");
    dataFile.print(a.acceleration.y);
    dataFile.print(",");
    dataFile.print(a.acceleration.z);
    dataFile.print(",");
    dataFile.print(g.gyro.x);
    dataFile.print(",");
    dataFile.print(g.gyro.y);
    dataFile.print(",");
    dataFile.print(g.gyro.z);
    dataFile.print(",");

//    dataFile.print(MS5611.getTemperature(), 3);
//    dataFile.print(",");
//    dataFile.print(MS5611.getPressure(), 3);
//    dataFile.print(",");
//    dataFile.print("\n");

    dataFile.print(bme.readTemperature());
    dataFile.print(",");
    dataFile.print(bme.readPressure() / 100.0F);
    dataFile.print(",");
    dataFile.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    dataFile.print(",");
    dataFile.print(bme.readHumidity());
    dataFile.print(",");


    dataFile.print("\nGPS:\n");
    //GPS
    while (ss.available() > 0){
      // get the byte data from the GPS
      byte gpsData = ss.read();
      Serial.write(gpsData);
      dataFile.write(gpsData);
    }
    dataFile.print("\n");
////////////////////////////////////////////////////////////save to SD
    
    dataFile.close();
    
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }

  delay(100); //can change this to set sensing rate
}

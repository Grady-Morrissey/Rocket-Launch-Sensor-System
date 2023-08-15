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
//https://www.amazon.com/HiLetgo-Adater-Interface-Conversion-Arduino/dp/B07BJ2P6X6/ref=sr_1_5?crid=23CV33Y6OXS7N&keywords=spi+sd+card+module&qid=1692141105&sprefix=spi+sd+card+%2Caps%2C193&sr=8-5

Functionality:
Saves sensor data as CSV to a TXT file on a micro SD card
After code is uploaded to Arduino Uno, sensor system will begin saving once board is powered. 
To improve functionality, adapt this code for use on a board with more memory. Arduino Uno runs out of memory, so not all sensors are used in this suite. Another board with more memory would allow for running all the sensors concurrently. 

Files:
I2C scanner reveals I2C devices connected to Arduino. 
WIPE_SD wipes SD card.
STL file is for a 3D printed box that can hold the sensors as well as some extra room. 
sensorcode is main code to be uploaded to Arduino. 
Example data file included. 


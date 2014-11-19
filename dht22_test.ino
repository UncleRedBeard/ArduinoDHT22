/***************************************************************
 * File:    dht22.ino                                          *
 * Author:  Uncle RedBeard                                     *
 * Date:    17-NOV-2014                                        *
 * Desc:    Connect DHT22 (AM2302) Temp and Humidity Sensor to *
 *          Arduino and write data to serial and log file on   *
 *          SD card                                            *
 * NOTE:    Original DHT22 sketch from ladyada                 *
 * ToDo:    Add function to turn on LED when temp hits 68*F    *
 *          18-NOV-2014                                        *
 *            add timer using millis() to enable ability to    *
 *            additional monitoring functionality              *
 ***************************************************************/

#include <SD.h>
#include <DHT.h>

#define DHTPIN 2       
#define DHTTYPE DHT22  // DHT 22 (AM2302)

DHT dht(DHTPIN, DHTTYPE);

File dhtFile;
const int CS = 4;
const int sensorPin = 0;

void setup(){
  Serial.begin(9600);
  
  Serial.println("***************************");
  Serial.println("Initializaing DHT22");
  
  dht.begin();
  
  Serial.println("Initializing SD card...");
  pinMode(10, OUTPUT);
  
  if (!SD.begin(4))
  {
    Serial.print("SD card initialization failed.");
    Serial.println(" ...did you remember to insert the SD card, dumbass?!?");
    return;
  }
  Serial.println("SD card initalized");
  Serial.println("***************************\n");
  
  if (SD.exists("dht22.csv")){
    SD.remove("dht22.csv");
  }
}

void loop(){
  delay(60000);
  
  float humidity = dht.readHumidity();
  //read temp as Celscius
  float tempC = dht.readTemperature();
  //read temp as Fahrenheit
  float tempF = dht.readTemperature(true);
  
  //check if any reads failed and exit early (to try again)
  if (isnan(humidity) || isnan(tempC) || isnan(tempF)) {
    Serial.println("\nFailed to read from DHT sensor!");
  }
  
  //compute heat index
  //must send in temp in Fahrentheit!
  float hi = dht.computeHeatIndex(tempF,humidity);
  
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print(" *C  | ");
  Serial.print(tempF);
  Serial.println(" *F\t");
  
  datalog(humidity, tempC, tempF);  
}

/*functions*/
void datalog(float a, float b, float c)
{
  dhtFile = SD.open("dht22.csv", FILE_WRITE);
  
  if (dhtFile) {
    dhtFile.print(a);
    dhtFile.print(",");
    dhtFile.print(b);
    dhtFile.print(",");
    dhtFile.println(c);
    dhtFile.close();
  } else {
    Serial.println("Error opening file");
  }
}


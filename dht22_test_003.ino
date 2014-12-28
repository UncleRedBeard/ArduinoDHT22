/*
 * File:    dht22_test_003.ino
 * Author:  Uncle RedBeard
 * Date:    22-DEC-2014
 * Desc:    reading temp and humidity from dht22 
 *          print sensor readings to serial via get_tempRH() function
 */
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

unsigned long interval = 15000;
unsigned long prevMillis = 0;

//----------------------------------------
void setup(){
  Serial.begin(9600);

  Serial.println("System starting");
  Serial.println("Please wait.\n");

  dht.begin();
}

//----------------------------------------
void get_tempRH(){
  float humidity = dht.readHumidity();
  float tempC = dht.readTemperature();
  float tempF = dht.readTemperature(true);
  
  if(isnan(humidity) || isnan(tempC) || isnan(tempF))  {
    
    Serial.println("\nFailed to read from DHT sensor");
    
  } else {
    
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
    Serial.print("Temp:  ");
    Serial.print(tempC);
    Serial.print("*C | ");
    Serial.print(tempF);
    Serial.println("*F");
  
  }
}

//----------------------------------------
void loop(){
  if(((unsigned long)(millis() - prevMillis)) >= interval){
    
    prevMillis = millis();
    
    get_tempRH();  
  }
}

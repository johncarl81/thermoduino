#include <SoftwareSerial.h>

#include "DHT.h"
#define DHTPIN 4     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

int deviceId = 1;

SoftwareSerial xbeeSerial(2,3);
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  xbeeSerial.begin(9600);
  
  dht.begin();
}

void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  xbeeSerial.print(buildReading(deviceId, h, (t * 9/5 + 32)));
  
  String content = "";
  boolean reading = false;
  while(xbeeSerial.available()){
    char c = xbeeSerial.read();
    if(c == 's'){
      reading = true;
      content = "";
    }
    
    if(reading){
      content.concat(c);
    }
    
    if(c == 'e'){
      reading = false;
      Serial.print("Validation: ");
      Serial.print(validate(content));
      Serial.print(" Content: ");
      Serial.println(content);
    }
  }
  
  delay(1000);
}

String buildReading(int id, float humidity, float temperature){
  
 String reading = "s"; //start

 reading.concat(id);
 reading.concat(",");
 reading.concat(floatToString(temperature));
 reading.concat(",");
 reading.concat(floatToString(humidity)); 
 reading.concat(",");
 reading.concat(checksum(reading));
 
 
 reading.concat("e"); //end
 
 return reading;
}

boolean validate(String reading){
  
  if(reading[0] != 's'){
    return false;
  } 
  if(reading[reading.length()-1] != 'e'){
    return false;
  }
  int commaCount = 0;
  int checksum = 0;
  for(int i = 0; i < reading.length() && commaCount < 3; i++){
    if(reading[i] == ','){
      commaCount++;
    }
    checksum += reading[i];
  }
  
  String inputCheckSumString = reading.substring(reading.lastIndexOf(",")+1, reading.length()-1);
  return checksum % 100 == inputCheckSumString.toInt();
}

String floatToString(float input){
   char buff[10];

   dtostrf(input,1,2,buff);
   return String(buff); 
}

int checksum(String input){
  int sum = 0;

  for(int i = 0; i < input.length(); i++){
    sum += input[i];
  } 
  return sum % 100;
}

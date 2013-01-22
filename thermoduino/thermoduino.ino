#include <SoftwareSerial.h>

#include "DHT.h"
#define DHTPIN 4     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

int deviceId = 2;
int loopVal = 0;

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
  loopVal++;
  
  if(loopVal == 100){
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    String reading = buildReading(deviceId, h, (t * 9/5 + 32));
    xbeeSerial.print(reading);
    outputValues(reading);
    loopVal = 0;
  }
  
  String content = "";
  boolean serialRead = false;
  while(xbeeSerial.available()){
    char c = xbeeSerial.read();
    if(c == 's'){
      serialRead = true;
      content = "";
    }
    
    if(serialRead){
      content.concat(c);
    }
    
    if(c == 'e'){
      serialRead = false;
      outputValues(content);
      parseValues(content);
    }
  }
  
  delay(10000);
}

void outputValues(String content){
  /*Serial.print("Validation: ");
      Serial.print(validate(content));
      Serial.print(" Content: ");
      Serial.println(content);*/
      parseValues(content);
}

void parseValues(String content){
 
  int firstComma = content.indexOf(",");
  int secondComma = content.indexOf(",", firstComma+1);
  int thirdComma = content.indexOf(",", secondComma+1);
  
  int id = content.substring(1,firstComma).toInt();
  float temperature = stringToFloat(content.substring(firstComma+1, secondComma));
  float humidity = stringToFloat(content.substring(secondComma+1, thirdComma));
  
  Serial.print("Id: ");
  Serial.print(id);
  Serial.print(" H: ");
  Serial.print(humidity);
  Serial.print(" T: ");
  Serial.print(temperature);
  Serial.print(" V: ");
  Serial.println(validate(content));
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

float stringToFloat(String input){
  char buff[input.length()];
  input.toCharArray(buff, input.length());
  return atof(buff);
}

int checksum(String input){
  int sum = 0;

  for(int i = 0; i < input.length(); i++){
    sum += input[i];
  } 
  return sum % 100;
}

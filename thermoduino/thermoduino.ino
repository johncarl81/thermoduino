#include <SoftwareSerial.h>
#if defined(ARDUINO) && ARDUINO > 18
#include <SPI.h>
#endif
#include <Twitter.h>        //load twitter library see http://www.arduino.cc/playground/Code/TwitterLibrary
#include <Ethernet.h>
#include "DHT.h"

#define DHTPIN 4     // what pin we're connected to
#define DHTTYPE DHT11  // DHT 22  (AM2302)

// Ethernet Shield Settings
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 1, 121 };

int deviceId = 3;
int loopVal = 0;
int twitterLoopVal = 0;
boolean enable_twitter = true;

SoftwareSerial xbeeSerial(2,3);
DHT dht(DHTPIN, DHTTYPE);

Twitter twitter("TODO");

void setup()
{
  Serial.begin(9600);
  xbeeSerial.begin(9600);
  Ethernet.begin(mac, ip);
  
  dht.begin();
}

void loop()
{
  loopVal++;
  twitterLoopVal++;
  
  if(loopVal == 100){
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    String reading = buildReading(deviceId, "R", h, (t * 9/5 + 32));
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
      xbeeSerial.print(content);
    }
  }
  
  delay(100);
}

void outputValues(String content){
 
  int firstComma = content.indexOf(",");
  int secondComma = content.indexOf(",", firstComma+1);
  int thirdComma = content.indexOf(",", secondComma+1);
  int forthComma = content.indexOf(",", thirdComma+1);
  
  int id = content.substring(1,firstComma).toInt();
  String type = content.substring(firstComma+1, secondComma);
  float temperature = stringToFloat(content.substring(secondComma+1, thirdComma));
  float humidity = stringToFloat(content.substring(thirdComma+1, forthComma));
  
  Serial.print("Id: ");
  Serial.print(id);
  Serial.print(" Type: ");
  Serial.print(type);
  Serial.print(" H: ");
  Serial.print(humidity);
  Serial.print(" T: ");
  Serial.print(temperature);
  Serial.print(" V: ");
  Serial.print(validate(content));
  Serial.print(" Time: ");
  Serial.println(twitterLoopVal);
  
  if(twitterLoopVal > 1200000 && validate(content)){
    twitterLoopVal = 0;
    Serial.println("TWEET!!");
    String message = "The current temperature is " + content.substring(secondComma+1, thirdComma) + "F from the office.";
    
    Serial.println(message);
    char messageBuff[message.length()];
    message.toCharArray(messageBuff, message.length());
    
    if (enable_twitter) {
     if(twitter.post(messageBuff)) {
      // Specify &Serial to output received response to Serial.
      // If no output is required, you can just omit the argument, e.g.
      // int status = twitter.wait();
      int status = twitter.wait(&Serial);
      if (status == 200) {
        Serial.println("OK.");
      } else {
        Serial.print("failed : code ");
        Serial.println(status);
      }
    } else {
      Serial.println("connection failed.");
    }
    }
    
  }
}

String buildReading(int id, String type, float humidity, float temperature){
  
 String reading = "s"; //start

 reading.concat(id);
 reading.concat(",");
 reading.concat(type);
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
  for(int i = 0; i < reading.length() && commaCount < 4; i++){
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

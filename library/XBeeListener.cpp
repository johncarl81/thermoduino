#include <XBeeListener.h>

XBeeListener::XBeeListener(SoftwareSerial *serial){
	_serial = serial;
}

String XBeeListener::floatToString(float input){
   char buff[10];
   dtostrf(input,1,2,buff);
   return String(buff); 
}

int XBeeListener::checksum(String input){
  int sum = 0;

  for(int i = 0; i < input.length(); i++){
    sum += input[i];
  } 
  return sum % 100;
}


String XBeeListener::buildReading(int id, String type, float humidity, float temperature, String name){
  
 String reading = "s"; //start

 reading.concat(id);
 reading.concat(",");
 reading.concat(type);
 reading.concat(",");
 reading.concat(floatToString(temperature));
 reading.concat(",");
 reading.concat(floatToString(humidity)); 
 reading.concat(",");
 reading.concat(name);
 reading.concat(",");
 reading.concat(checksum(reading));
 
 reading.concat("e"); //end
 
 return reading;
}

void XBeeListener::listen(int id, float tempurature, float humidity, String location){
	String value = buildReading(id, "R", humidity, tempurature, location);
	_serial->print(value);
}
	

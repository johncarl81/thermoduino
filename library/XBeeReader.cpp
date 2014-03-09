#include <XBeeReader.h>

void XBeeReader::read(ThermoduinoListener* listener){

  String content = "";
  boolean serialRead = false;
  while(_xbeeSerial->available()){
    char c = _xbeeSerial->read();
    if(c == '~'){
      serialRead = true;
      content = "";
    }
    
    if(serialRead){
      content.concat(c);
    }
    
    if(c == '*'){
      serialRead = false;
	parseRun(content, listener);
    }
  }
}
	
void XBeeReader::parseRun(String content, ThermoduinoListener* listener){
 
  int firstComma = content.indexOf(",");
  int secondComma = content.indexOf(",", firstComma+1);
  int thirdComma = content.indexOf(",", secondComma+1);
  int forthComma = content.indexOf(",", thirdComma+1);
  int fifthComma = content.indexOf(",", forthComma+1);
  
  int id = content.substring(1,firstComma).toInt();
  String type = content.substring(firstComma+1, secondComma);
  float temperature = stringToFloat(content.substring(secondComma+1, thirdComma));
  float humidity = stringToFloat(content.substring(thirdComma+1, forthComma));
  String name = content.substring(forthComma+1, fifthComma);

	listener->listen(id, temperature, humidity, name);
}

boolean XBeeReader::validate(String reading){
  
  if(reading[0] != 's'){
    return false;
  } 
  if(reading[reading.length()-1] != 'e'){
    return false;
  }
  int commaCount = 0;
  int checksum = 0;
  for(int i = 0; i < reading.length() && commaCount < 5; i++){
    if(reading[i] == ','){
      commaCount++;
    }
    checksum += reading[i];
  }
  
  String inputCheckSumString = reading.substring(reading.lastIndexOf(",")+1, reading.length()-1);
  return checksum % 100 == inputCheckSumString.toInt();
}

float XBeeReader::stringToFloat(String input){
  char buff[input.length()];
  input.toCharArray(buff, input.length());
  return atof(buff);
}

int XBeeReader::checksum(String input){
  int sum = 0;

  for(int i = 0; i < input.length(); i++){
    sum += input[i];
  } 
  return sum % 100;
}

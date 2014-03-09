#include <LoggerListener.h>


void LoggerListener::listen(int id, float tempurature, float humidity, String location){
	Serial.print("Id: ");
	  Serial.print(id);
	  Serial.print(" H: ");
	  Serial.print(humidity);
	  Serial.print(" T: ");
	  Serial.print(tempurature);
	  Serial.print(" Name: ");
	  Serial.println(location);
}
	

#include <TwitterListener.h>

TwitterListener::TwitterListener(Twitter *twitter){
	_twitter = twitter;
	twitterLoopVal = 0;
}

String innerFloatToString(float input){
   char buff[10];
   dtostrf(input,1,2,buff);
   return String(buff); 
}

void TwitterListener::listen(int id, float tempurature, float humidity, String location){
	String message = "The current temperature is " + innerFloatToString(tempurature) + "F from the " + location + ".";	
	Serial.println("TWEET!! " + message + " Loop: " + twitterLoopVal);
	/*if(twitter->post(messageBuff)) {
      // Specify &Serial to output received response to Serial.
      // If no output is required, you can just omit the argument, e.g.
      // int status = twitter.wait();
      int status = twitter->wait(&Serial);
      if (status == 200) {
        Serial.println("OK.");
      } else {
        Serial.print("failed : code ");
        Serial.println(status);
      }
    } else {
      Serial.println("connection failed.");
    }*/
	twitterLoopVal++;
}
	

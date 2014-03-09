#ifndef TWITTER_LISTENER_H
#define TWITTER_LISTENER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <Twitter.h>        //load twitter library see http://www.arduino.cc/playground/Code/TwitterLibrary
#include <ThermoduinoListener.h>

class TwitterListener : public ThermoduinoListener {
public:
	TwitterListener(Twitter *twitter);
	void listen(int id, float tempurature, float humidity, String location);
private:

	Twitter *_twitter;
};

#endif

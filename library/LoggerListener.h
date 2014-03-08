#ifndef LOGGER_LISTENER_H
#define LOGGER_LISTENER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <ThermoduinoListener.h>

class LoggerListener : public ThermoduinoListener {
public:
	LoggerListener();
	void listen(int id, float tempurature, float humidity, String location);
private:
	int loopVal;
};

#endif

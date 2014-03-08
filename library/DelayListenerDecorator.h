#ifndef DELAY_LISTENER_H
#define DELAY_LISTENER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <ThermoduinoListener.h>

class DelayListenerDecorator : public ThermoduinoListener {
public:
	DelayListenerDecorator(ThermoduinoListener *listener, int threshold);
	void listen(int id, float tempurature, float humidity, String location);
private:
	int _loopVal;
	int _threshold;
	ThermoduinoListener *_listener;
};

#endif

#ifndef COMPOSITE_LISTENER_H
#define COMPOSITE_LISTENER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <ThermoduinoListener.h>

class ListenerComposite : public ThermoduinoListener {
public:
	ListenerComposite(ThermoduinoListener **listeners, int size);
	void listen(int id, float tempurature, float humidity, String location);
private:
	ThermoduinoListener **_listeners;
	int _size;
};

#endif

#ifndef XBEE_LISTENER_H
#define XBEE_LISTENER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <SoftwareSerial.h>
#include <ThermoduinoListener.h>

class XBeeListener : public ThermoduinoListener {
public:
	XBeeListener(SoftwareSerial *serial);
	void listen(int id, float tempurature, float humidity, String location);
private:

	String floatToString(float input);
	int checksum(String input);
	String buildReading(int id, String type, float humidity, float temperature, String name);

	SoftwareSerial *_serial;
};

#endif

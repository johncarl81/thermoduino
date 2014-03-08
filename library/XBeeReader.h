#ifndef XBEE_READER_H
#define XBEE_READER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <ThermoduinoListener.h>
#include <SoftwareSerial.h>

class XBeeReader {
public:
	XBeeReader(SoftwareSerial*  xbeeSerial){_xbeeSerial = xbeeSerial;};
	void read(ThermoduinoListener* listener);

private:
	void parseRun(String content, ThermoduinoListener* listener);
	boolean validate(String reading);
	float stringToFloat(String input);
	int checksum(String input);

	SoftwareSerial*  _xbeeSerial;
};

#endif

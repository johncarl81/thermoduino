#ifndef TEMP_READER_H
#define TEMP_READER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <ThermoduinoListener.h>
#include "DHT.h"

class TempuratureReader {
public:
	TempuratureReader(String location, int deviceId, DHT* dht){_deviceId = deviceId; _dht = dht; _location = location;};
	void read(ThermoduinoListener* listener);

private:
	DHT* _dht;
	int _deviceId;
	String _location;
};

#endif

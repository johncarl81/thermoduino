#ifndef THERMODUINO_LISTENER_H
#define THERMODUINO_LISTENER_H

class ThermoduinoListener {
public:
	virtual void listen(int id, float tempurature, float humidity, String location) = 0;
};

#endif

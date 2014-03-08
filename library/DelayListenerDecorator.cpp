#include <DelayListenerDecorator.h>

DelayListenerDecorator::DelayListenerDecorator(ThermoduinoListener *listener, int threshold){
	_listener = listener;
	_loopVal = 0;
	_threshold = threshold;
}

void DelayListenerDecorator::listen(int id, float tempurature, float humidity, String location){
	_loopVal++;
	if(_loopVal >= _threshold){
		_listener->listen(id, tempurature, humidity, location);
		_loopVal = 0;
	}
}
	

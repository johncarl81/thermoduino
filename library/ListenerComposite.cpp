#include <ListenerComposite.h>

ListenerComposite::ListenerComposite(ThermoduinoListener **listeners, int size){
	_listeners = listeners;
	_size = size;
}

void ListenerComposite::listen(int id, float tempurature, float humidity, String location){
	for(int i = 0; i < _size; i++){
		_listeners[i]->listen(id, tempurature, humidity, location);
	}
}
	

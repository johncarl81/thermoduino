#include <TempuratureReader.h>

void TempuratureReader::read(ThermoduinoListener* listener){
    float h = _dht->readHumidity();
    float t = _dht->readTemperature();
    listener->listen(_deviceId, (t * 9/5 + 32), h, _location);
}
	

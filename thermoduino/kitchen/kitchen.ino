
#include <SoftwareSerial.h>
#if defined(ARDUINO) && ARDUINO > 18
#include <SPI.h>
#endif
#include <Twitter.h>        //load twitter library see http://www.arduino.cc/playground/Code/TwitterLibrary
#include <Ethernet.h>
#include "DHT.h"
#include <XBeeListener.h>
#include <LoggerListener.h>
#include <DelayListenerDecorator.h>
#include <ListenerComposite.h>
#include <TempuratureReader.h>
#include <XBeeReader.h>

#define DHTPIN 4     // what pin we're connected to
#define DHTTYPE DHT11 // DHT 11  (AM2302)

SoftwareSerial xbeeSerial(2,3);
DHT dht(DHTPIN, DHTTYPE);

XBeeListener xbeeListener(&xbeeSerial);
LoggerListener loggerListener;
ThermoduinoListener* listenerCollection[2] = {&xbeeListener, &loggerListener};

ListenerComposite composite(listenerCollection, 2);

TempuratureReader tempuratureReader("Kitchen", 2, &dht);
XBeeReader xbeeReader(&xbeeSerial);

int loopVal = 0;

void setup()
{
  Serial.begin(9600);
  xbeeSerial.begin(9600);
  dht.begin();
}

void loop()
{
  loopVal++;

  tempuratureReader.read(&composite);
  xbeeReader.read(&loggerListener);

  delay(100000);
}



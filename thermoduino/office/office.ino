
#include <SoftwareSerial.h>
#if defined(ARDUINO) && ARDUINO > 18
#include <SPI.h>
#endif
#include <Twitter.h>        //load twitter library see http://www.arduino.cc/playground/Code/TwitterLibrary
#include <Ethernet.h>
#include "DHT.h"
#include <TwitterListener.h>
#include <XBeeListener.h>
#include <LoggerListener.h>
#include <DelayListenerDecorator.h>
#include <ListenerComposite.h>
#include <TempuratureReader.h>
#include <XBeeReader.h>

#define DHTPIN 4     // what pin we're connected to
#define DHTTYPE DHT22  // DHT 22  (AM2302)

// Ethernet Shield Settings
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 1, 121 };

SoftwareSerial xbeeSerial(2,3);
DHT dht(DHTPIN, DHTTYPE);

Twitter twitter("1123581661-a54CmLmx02kpDsXbMf0hgsI864fpIhSSe8xuQVl");

TwitterListener twitterListener(&twitter);
DelayListenerDecorator twitterDecorator(&twitterListener, 400);
XBeeListener xbeeListener(&xbeeSerial);
LoggerListener loggerListener;
ThermoduinoListener* listenerCollection[3] = {&twitterDecorator, &xbeeListener, &loggerListener};

ListenerComposite composite(listenerCollection, 3);

ThermoduinoListener* inputListenerCollection[2] = {&twitterDecorator, &loggerListener};

ListenerComposite inputComposite(inputListenerCollection, 2);

TempuratureReader tempuratureReader("Office", 1, &dht);
XBeeReader xbeeReader(&xbeeSerial);

int loopVal = 0;

void setup()
{
  Serial.begin(9600);
  xbeeSerial.begin(9600);
  Ethernet.begin(mac, ip);
  dht.begin();
}

void loop()
{
  loopVal++;

  tempuratureReader.read(&composite);
  xbeeReader.read(&inputComposite);

  delay(100000);
}



/*-------------------------------------------------------------------------------------------------------


							Example ESP Manager software..

BeerWare Licence, just give due credits

Upload files to the ESP using this command (on mac and linux anyway, can upload using serial via SPIFFS data upload too)
for file in `ls -A1`; do curl -F "file=@$PWD/$file" X.X.X.X/espman/upload; done
 * Thanks to me-no-dev

--------------------------------------------------------------------------------------------------------*/
#include <FS.h> //  Settings saved to SPIFFS
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266WebServer.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h> // required for settings file to make it readable

#include <ESPmanager.h>

#include "FastLED.h"
#define NUM_LEDS 12
#define DATA_PIN 2



ESP8266WebServer HTTP(80);

ESPmanager settings(HTTP, SPIFFS, "ESPManager");

CRGB leds[NUM_LEDS];

void setup()
{

	Serial.begin(115200);
	SPIFFS.begin();

	Serial.println("");
	Serial.println(F("Example ESPconfig"));

	Serial.printf("Sketch size: %u\n", ESP.getSketchSize());
	Serial.printf("Free size: %u\n", ESP.getFreeSketchSpace());

	settings.begin();

	HTTP.begin();

	Serial.print(F("Free Heap: "));
	Serial.println(ESP.getFreeHeap());

  Serial.print(F("Hello world"));
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);

}


void loop()
{
	HTTP.handleClient();
	settings.handle();

  // Move a single white led
   for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
      // Turn our current led on to white, then show the leds
      leds[whiteLed] = CRGB::White;

      // Show the leds (only one of which is set to white, from above)
      FastLED.show();

      // Wait a little bit
      delay(500);

      // Turn our current led back to black for the next loop around
      leds[whiteLed] = CRGB::Black;
   }
}

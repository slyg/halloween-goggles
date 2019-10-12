#include <Adafruit_NeoPixel.h>

#define LED_PIN    6
#define LED_COUNT 16

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(15); // Set BRIGHTNESS to about 1/5 (max = 255)
}


void loop() {

  float hueInitialFactor = 0;
  float hueIntervalFactor = 0.2;
  long pixelHueStart = hueInitialFactor * 65536;
  long pixelHueEnd = (hueInitialFactor + hueIntervalFactor) * 65536;
  long hueInterval = hueIntervalFactor * 65536L / LED_COUNT;
  int delayBetweenUpdates = 10;

  for(int shift = 0; shift < LED_COUNT; shift++) {

    int modShift = shift % LED_COUNT;

    for(int i=0; i < LED_COUNT; i++) {
      int pixelHue = pixelHueStart + (i * hueInterval);
      setPixelHue((i + modShift) % LED_COUNT, pixelHue);
      strip.show();
    }

    delay(delayBetweenUpdates);

  }
}

void setPixelHue(int i, long hue) {
  strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(hue)));
}

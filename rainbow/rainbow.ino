#include <Adafruit_NeoPixel.h>

#define LED_PIN_RIGHT   6
#define LED_PIN_LEFT    7
#define LED_COUNT      16

Adafruit_NeoPixel ringRight = Adafruit_NeoPixel(LED_COUNT, LED_PIN_RIGHT, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ringLeft = Adafruit_NeoPixel(LED_COUNT, LED_PIN_LEFT, NEO_GRB + NEO_KHZ800);

void setup() {
  ringSetup(ringRight);
  ringSetup(ringLeft);
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
    }

    delay(delayBetweenUpdates);

  }
}

void ringSetup(Adafruit_NeoPixel &ring) {
  ring.begin();
  ring.show();            // Turn OFF all pixels ASAP
  ring.setBrightness(15); // Set BRIGHTNESS to about 1/5 (max = 255)
}


void setPixelHue(int i, long hue) {
  ringRight.setPixelColor(i, ringRight.gamma32(ringRight.ColorHSV(hue)));
  ringRight.show();
  ringLeft.setPixelColor(i, ringLeft.gamma32(ringLeft.ColorHSV(hue)));
  ringLeft.show();
}

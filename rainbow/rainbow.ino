#include <Adafruit_NeoPixel.h>

#define LED_PIN_RIGHT      6
#define LED_PIN_LEFT       7
#define LED_COUNT         16  // 16 leds rings
#define RINGS_BRIGHTNESS  20  // (0 to 255)
#define HUE_RANGE         65536 // Number of possible hue values

Adafruit_NeoPixel ringRight = Adafruit_NeoPixel(LED_COUNT, LED_PIN_RIGHT, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ringLeft = Adafruit_NeoPixel(LED_COUNT, LED_PIN_LEFT, NEO_GRB + NEO_KHZ800);

void setup() {
  ringSetup(ringRight);
  ringSetup(ringLeft);
}

void loop() {
  long pixelHueStart = 0; // Red
  long pixelHueEnd = HUE_RANGE/6; // Orange
  long hueInterval = 256;
  int delayBetweenUpdates = 10;

  for(int hue = pixelHueStart; hue < pixelHueEnd; hue += hueInterval) {
    setRingsHue(hue);
    delay(delayBetweenUpdates);
  }

  delay(random(1000, 20000));
  
  for(int hue = pixelHueEnd; hue > pixelHueStart; hue -= hueInterval) {
    setRingsHue(hue);
    delay(delayBetweenUpdates);
  }

  delay(random(1000, 20000));
}

void ringSetup(Adafruit_NeoPixel &ring) {
  ring.begin();
  ring.show(); // Turn OFF all pixels ASAP
  ring.setBrightness(RINGS_BRIGHTNESS);
}

void setRingsHue(long hue) {
  for(int i=0; i < LED_COUNT; i++) {
    ringRight.setPixelColor(i, ringRight.gamma32(ringRight.ColorHSV(hue, 255, 255)));
    ringLeft.setPixelColor(i, ringLeft.gamma32(ringLeft.ColorHSV(hue, 255, 255)));
  }
  ringRight.show();
  ringLeft.show();
}

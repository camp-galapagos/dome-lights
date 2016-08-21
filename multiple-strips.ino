
#include <strip.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include <Strip.h>

#define NUM_STRIPS 7
#define NUM_PIXELS_PER_STRIP 29

int NUMPIXEL_EACH_STRIP[7]=
{9,9,10,6,8,5,11};

int NUMPIXEL[7][2]=
{
{6,3},
{5,4},
{5,5},
{3,3},
{5,3},
{2,3},
{8,3},
};

Adafruit_NeoPixel *strips[NUM_STRIPS];



  
void setup() {
    // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  for (int i = 0; i < NUM_STRIPS; i++) {
    strips[i] = new Adafruit_NeoPixel(
   NUMPIXEL_EACH_STRIP[i], i, NEO_GRB + NEO_KHZ800);
    strips[i]->begin();
    strips[i]->show();
  }
}

void loop() {
  rainbow(20);
}


void rainbow(uint8_t wait) {
  uint16_t base, strip, pixel, color, pixelCount;

  // For each color.
  for (base = 0; base < 256 ; base++) {
    // For each strip.
    for (strip = 0; strip < NUM_STRIPS; strip++) {
      // Set a color for each pixel in that strip.
      pixelCount = strips[strip]->numPixels();
      for (pixel = 0; pixel < pixelCount; pixel++) {
        strips[strip]->setPixelColor(
            pixel, Wheel((base + strip * 30) & 255));
      }
      strips[strip]->show();
      delay(wait);
    }
    // delay(wait);
  }
};

  
uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
  return Adafruit_NeoPixel::Color(r, g, b);
}




// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

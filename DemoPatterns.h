#ifndef _DEMO_PATTERNS_H
#define _DEMO_PATTERNS_H

void rainbow() {
  static uint8_t hue = 0;
  
  fill_rainbow( leds, NUM_LEDS, hue++, 7);
  FastLED.show();

  delay(DELAY / 2);
}

#endif

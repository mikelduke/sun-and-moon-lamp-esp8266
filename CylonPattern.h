#ifndef _CYLON_PATTERN_H
#define _CYLON_PATTERN_H

void cylon() {
    static uint8_t hue = 0;
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(hue++, 255, 255);
        FastLED.show();
        // leds[i] = CRGB::Black;
        fadeall();
        delay(DELAY);
    }
    //	for(int i = (NUM_LEDS)-1; i >= 0; i--) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(hue++, 255, 255);
        FastLED.show();
        // leds[i] = CRGB::Black;
        fadeall();
        delay(DELAY);
    }
}

void whiteCylon() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::White;
        FastLED.show();
        leds[i] = CRGB::Black;
        // fadeall();
        delay(DELAY);
    }
    //	for(int i = (NUM_LEDS)-1; i >= 0; i--) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::White;
        FastLED.show();
        leds[i] = CRGB::Black;
        // fadeall();
        delay(DELAY);
    }
}

#endif

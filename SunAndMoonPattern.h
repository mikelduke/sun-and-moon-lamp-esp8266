#ifndef _SUN_AND_MOON_PATTERN_H
#define _SUN_AND_MOON_PATTERN_H

// NTP : NTPClient:3.1.0
// https://github.com/arduino-libraries/NTPClient/
#include <NTPClient.h>
#include <WiFiUdp.h>

#include <EEPROM.h>
#include "EEPromAddresses.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

boolean initTime = false;

//Lamp has two strips of leds connected at one end
//Sun LEDS #0,1,2,7,8,9
//Moon LEDS #3,4,5,6

uint8_t sunStartHour;
uint8_t sunStartMin;
uint8_t moonStartHour;
uint8_t moonStartMin;

void boundsCheck();

void setTimes(uint8_t sunStartH, uint8_t sunStartM, uint8_t moonStartH, uint8_t moonStartM) {
    sunStartHour = sunStartH;
    sunStartMin = sunStartM;
    moonStartHour = moonStartH;
    moonStartMin = moonStartM;
    boundsCheck();

    EEPROM.write(EEPROM_SUN_START_HR, sunStartHour);
    EEPROM.write(EEPROM_SUN_START_MIN, sunStartMin);
    EEPROM.write(EEPROM_MOON_START_HR, moonStartHour);
    EEPROM.write(EEPROM_MOON_START_MIN, moonStartMin);
    EEPROM.commit();
}

void boundsCheck() {
    if (moonStartHour < 0) moonStartHour = 20;
    else if (moonStartHour > 23) moonStartHour = 20;

    if (moonStartMin < 0) moonStartMin = 0;
    else if (moonStartMin > 59) moonStartMin = 0;

    if (sunStartHour < 0) sunStartHour = 8;
    else if (sunStartHour > 23) sunStartHour = 8;

    if (sunStartMin < 0) sunStartMin = 0;
    else if (sunStartMin > 59) sunStartMin = 0;
}

void loadTimeSettings() {
    sunStartHour = EEPROM.read(EEPROM_SUN_START_HR);
    sunStartMin = EEPROM.read(EEPROM_SUN_START_MIN);
    moonStartHour = EEPROM.read(EEPROM_MOON_START_HR);
    moonStartMin = EEPROM.read(EEPROM_MOON_START_MIN);

    boundsCheck();
}

void setupTime() {
    loadTimeSettings();

    timeClient.setUpdateInterval(5 * 60 * 1000); // 5 minutes
    timeClient.setTimeOffset(- 5 * 60 * 60); // -5hours CDT, -6hours CST
    timeClient.begin();
    initTime = true;

    timeClient.update();
}

void lightSun() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }
    leds[0] = CRGB::White;
    leds[1] = CRGB::White;
    leds[2] = CRGB::White;

    leds[7] = CRGB::White;
    leds[8] = CRGB::White;
    leds[9] = CRGB::White;
    FastLED.show();
}

void lightMoon() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }
    leds[3] = CRGB::White;
    leds[4] = CRGB::White;
    leds[5] = CRGB::White;
    leds[6] = CRGB::White;
    FastLED.show();
}

void sunAndMoonPattern() {
    if (!initTime) {
        setupTime();
    }

    timeClient.update();
    int hours = timeClient.getHours();
    int minutes = timeClient.getMinutes();

    //assumes moon hour > sun hour
    if (hours > sunStartHour && hours < moonStartHour) {
        lightSun();
    } else if (hours == sunStartHour) {
        if (minutes >= sunStartMin) {
            lightSun();
        } else {
            lightMoon();
        }
    } else if (hours == moonStartHour) {
        if (minutes >= moonStartMin) {
            lightMoon();
        } else {
            lightSun();
        }
    } else {
        lightMoon();
    }

    delay(DELAY);
}

#endif

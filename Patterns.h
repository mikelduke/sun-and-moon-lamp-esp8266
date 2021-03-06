#ifndef _PATTERNS_H
#define _PATTERNS_H

#include "BasicPatterns.h"
#include "DemoPatterns.h"
#include "CylonPattern.h"
#include "SunAndMoonPattern.h"

extern uint8_t currentPatternIndex = 0;

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

typedef void (*Pattern)();
typedef Pattern PatternList[];
typedef struct {
  Pattern pattern;
  String name;
} PatternAndName;
typedef PatternAndName PatternAndNameList[];

// Add new patterns here
extern PatternAndNameList patterns = {
  { cylon,                 "Cylon" },
  { whiteCylon,            "Cylon White" },
  { ring,                  "Ring" },
  { ring_two,              "Ring Type 2" },
  { huefade,               "Hue Fade" },
  { rainbow,               "Rainbow" },
  { white,                 "Set to White"},
  { red,                   "Set to Red"},
  { blue,                  "Set to Blue"},
  { green,                 "Set to Green"},
  { sunAndMoonPattern,     "Sun And Moon" }
};

extern const uint8_t patternCount = ARRAY_SIZE(patterns);

void setPattern(uint8_t value) {
  if (value >= patternCount)
    value = patternCount - 1;

  currentPatternIndex = value;

  EEPROM.write(EEPROM_LAST_MODE, currentPatternIndex);
  EEPROM.commit();

  Serial.printf("Pattern: %d\n", currentPatternIndex);
}

#endif

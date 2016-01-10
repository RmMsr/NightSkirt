/* Illuminates a skirt with 3 circles of 12 leds.
 * 
 * The 36 leds are controlled via 2 sn3218 led drivers.
 * See: https://github.com/pimoroni/pimoroni_arduino_sn3218
 */

#include "sn3218_software_wire.h"

const int NUM_LED = 36;            // Number of Leds
const unsigned char LED_OFF = 0;   // Minimal brightness
const unsigned char LED_MAX = 127; // Maximal brightness

sn3218_SoftwareWire* driver_1;     // First led driver
sn3218_SoftwareWire* driver_2;     // Second led driver

unsigned char ledStates[NUM_LED];  // Brightness per led
char ledChanges[NUM_LED];          // Glowing speed per led

void setup()
{
  // setup first led controller
  driver_1 = new sn3218_SoftwareWire(2, 3);
  driver_1->begin();
  driver_1->enable_leds(SN3218_CH_ALL);

  // setup second led controller
  driver_2 = new sn3218_SoftwareWire(11, 10);
  driver_2->begin();
  driver_2->enable_leds(SN3218_CH_ALL);

  // Initialize random number generator
  randomSeed(analogRead(0));

  // Start with random pattern
  randomInit();
  displayLeds();
}

void loop()
{
  glowAll();
  delay(128);
}

// Turn all leds dark
void allLedsOff()
{
  for (int current = 0; current < NUM_LED; current++) {
    ledStates[current] = LED_OFF;
  }
  displayLeds();
}

// Turn all leds brigth
void allLedsOn()
{
  for (int current = 0; current < NUM_LED; current++) {
    ledStates[current] = LED_MAX;
  }
  displayLeds();
}

// Initialize leach eds with random brightness and speed 
void randomInit()
{
  for (int led = 0; led < NUM_LED; led++) {
    ledStates[led] = random(0, LED_MAX + 1);
    char max = 8;
    /* produce numbers from -max to max excluding 0 */
    ledChanges[led] = random(1, 2 * max + 1);
    if (ledChanges[led] > max) {
       ledChanges[led] -= 2 * max - 1;
    }
  }
}

// Animate all leds with their speed
void glowAll()
{
  for (int led = 0; led < NUM_LED; led++) {
    long brightness = (long) ledStates[led];
    brightness += ledChanges[led];
    if (brightness < LED_OFF) {
      brightness = LED_OFF;
      ledChanges[led] *= -1;
    } else if (brightness > LED_MAX) {
      brightness = LED_MAX;
      ledChanges[led] *= -1;
    }
    ledStates[led] = (unsigned char) brightness;
  }  
  displayLeds();
}

// Turn each led on once
void cycleLeds()
{
  int lastLed = NUM_LED - 1;
  for (int currentLed = 0; currentLed < NUM_LED; currentLed++) {
    ledStates[currentLed] = LED_MAX;
    ledStates[lastLed] = LED_OFF;
    displayLeds();
    delay(50);
    lastLed = currentLed;
  }
  displayLeds();
}

// Show all leds with their configured brightness
void displayLeds()
{
  for (int led = 0; led < 18; led++) {
    driver_1->set(led, ledStates[led]);
    driver_2->set(led, ledStates[led + 18]);
  }
  driver_1->update();
  driver_2->update();
}


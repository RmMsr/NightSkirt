/* Illuminates a skirt with 3 circles of 12 leds.
 * 
 * The 36 leds are controlled via 2 sn3218 led drivers.
 * See: https://github.com/pimoroni/pimoroni_arduino_sn3218
 */

#include "sn3218_software_wire.h"

const int NUM_LED = 36;            // Number of leds
const unsigned char LED_MIN = 0;   // Minimal brightness
const unsigned char LED_MAX = 127; // Maximal brightness

sn3218_SoftwareWire* driver_1;     // First led driver
sn3218_SoftwareWire* driver_2;     // Second led driver

float ledStates[NUM_LED];          // Brightness per led
float ledChanges[NUM_LED];         // Brightness Delta per led

const unsigned int loopDelay = 30; // Wait time between loops
const float glowSpeed = 0.02;      // Animation speed 0.0 < x < 1.0

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
  delay(loopDelay);
}

// Turn all leds dark
void allLedsOff()
{
  for (int current = 0; current < NUM_LED; current++) {
    ledStates[current] = LED_MIN;
  }
  displayLeds();
}

// Turn all leds bright
void allLedsOn()
{
  for (int current = 0; current < NUM_LED; current++) {
    ledStates[current] = LED_MAX;
  }
  displayLeds();
}

// Initialize each leds with random brightness and speed 
void randomInit()
{
  for (int led = 0; led < NUM_LED; led++) {
    ledStates[led] = (float) random(RAND_MAX) / RAND_MAX;
    ledChanges[led] = ((float) random(RAND_MAX) / RAND_MAX - 0.5) * glowSpeed;
  }
}

// Animate all leds with their speed
void glowAll()
{
  for (int led = 0; led < NUM_LED; led++) {
    float brightness = ledStates[led];
    brightness += ledChanges[led];
    if (brightness < 0) {
      brightness = 0;
      ledChanges[led] *= -1;
    } else if (brightness > 1) {
      brightness = 1;
      ledChanges[led] *= -1;
    }
    ledStates[led] = brightness;
  }  
  displayLeds();
}

// Turn on each led once
void cycleLeds()
{
  int lastLed = NUM_LED - 1;
  for (int currentLed = 0; currentLed < NUM_LED; currentLed++) {
    ledStates[currentLed] = LED_MAX;
    ledStates[lastLed] = LED_MIN;
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
    driver_1->set(led, ledGradient(ledStates[led]));
    driver_2->set(led, ledGradient(ledStates[led + 18]));
  }
  driver_1->update();
  driver_2->update();
}

// Compute output values for SN3218 driver
// Param brigtness [float] (0.0 - 1.0)
// Return [uint8_t] 0 - 255
uint8_t ledGradient(float brightness)
{
  // Change gradient to to be off for lower values.
  // Brightness increases exponentially
  float adjusted = powf(0.7 * brightness + 0.12, 20) * 50;
  return max(
    min((uint8_t) (adjusted * LED_MAX), LED_MAX), 
    LED_MIN);
}


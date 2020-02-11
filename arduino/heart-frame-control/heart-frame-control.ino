// Top Level Includes
#include <Adafruit_NeoPixel_ZeroDMA.h>


// Definitions
#define PIN 4
#define NUM_PIXELS 144
#define BUTTON_PIN 2

// Variables
int seq = 0;
//volatile int touchState = 0;


Adafruit_NeoPixel_ZeroDMA strip(NUM_PIXELS, PIN, NEO_GRB);

//  function for creating external interrupts at pin1 on Rising (LOW to HIGH)

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), sequenceSelect, RISING);
  strip.begin();
  strip.setBrightness(5);
  //  strip.Color(255, 0, 0);
  //  strip.show(); // Initialize to solid red
}

void loop() {
  //  changeDisplay();
  solidRed();
  // wait for button to be pressed
  // on press - run sequence incrementer
  //if(buttonPressed) {
  //  sequenceSelect();
  //}

}
void sequenceSelect() {
  if (seq < 6) {
    seq = seq + 1;
  } else {
    seq = 0;
  }
}

void changeDisplay() {
  {
    switch (seq)
    {
      case 0: solidRed(); break;
      case 1: outlineWipe(); break;
      case 2: outlineBrightnessWipe(); break;
      case 3: theaterChase(strip.Color(255,   0,   0), 50); break;
      case 4: rainbow(10); break;
    }
  }
}

void solidRed() {
  for (int i = 0; i < NUM_PIXELS; i++) {
    strip.setPixelColor(i, 0xFF0000);
  }
  strip.show();
}

void outlineWipe() {
  int mid = (NUM_PIXELS / 2) - 1;
  while (true) {
    for (int a = mid; a >= 0; a--) {
      strip.setPixelColor(a, 0xFF0000);
      int difference = mid - a;
      int b = mid + difference;
      strip.setPixelColor(b, 0xFF0000);
      strip.show();
      delay(50);
    }
    for (int a = mid; a >= 0; a--) {
      strip.setPixelColor(a, 0x000000);
      int difference = mid - a;
      int b = mid + difference;
      strip.setPixelColor(b, 0x000000);
      strip.show();
      delay(50);
    }
    delay(100);
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for (int a = 0; a < 10; a++) { // Repeat 10 times...
    for (int b = 0; b < 3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for (int c = b; c < strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

void outlineBrightnessWipe() {
  int mid = (NUM_PIXELS / 2) - 1;
  while (true) {
    for (int a = mid; a >= 0; a--) {
      strip.setPixelColor(a, 255, 0, 0);
      int difference = mid - a;
      int b = mid + difference;
      strip.setPixelColor(b, 255, 0, 0);
      if (difference > 0) {
        int fadeLength = difference;
        int loopItem = 0;
        if (difference > 10) {
          fadeLength = 10;
        }
        while (loopItem <= fadeLength) {
          int fadeValue = 255 - (loopItem * 20);
          strip.setPixelColor(a + loopItem, fadeValue, 0, 0);
          strip.setPixelColor(b - loopItem, fadeValue, 0, 0);
          loopItem++;
        }
      }
      strip.show();
      delay(50);
    }
    delay(100);
  }
}


void solidChiefs() {
  int mid = (NUM_PIXELS / 2) - 1;
  for (int i = 0; i < mid; i++) {
    strip.setPixelColor(i, 0xE31837);
  }
  for (int i = mid + 1; i < NUM_PIXELS; i++) {
    strip.setPixelColor(i, 0xFFB81C);
  }
  strip.show();
}

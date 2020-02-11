// Top Level Includes
#include <Adafruit_NeoPixel_ZeroDMA.h>


// Definitions
#define PIN 4
#define NUM_PIXELS 144

// Variables
int seq = 0;
//volatile int touchState = 0;


Adafruit_NeoPixel_ZeroDMA strip(NUM_PIXELS, PIN, NEO_GRB);

//  function for creating external interrupts at pin1 on Rising (LOW to HIGH)

void setup() {
  //  attachInterrupt(digitalPinToInterrupt(1),sequenceSelect,RISING);
  //    pinMode(touchState, INPUT);

  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(5);
  strip.Color(255, 0, 0);
  strip.show(); // Initialize to solid red
}

void loop() {
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
//      case 2: redPulse(); break;
//      case 3: redBrightChase(); break;
//      case 4: heartBeat(); break;
//      case 5: chiefsSolid(); break;
//      case 6: redTwinkle(); break;
//      case 7: rainbowCycle(); break;
    }
  }
}

void solidRed() {
  strip.Color(255, 0,0);
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
    delay(100);
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

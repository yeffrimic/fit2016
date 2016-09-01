/*
 * firmware made in FIT2016 
 * materials
 * hc-05 bluetooth module
 * neopixel Ring 
 * arduino Gemma v2
 * battery 3.7 volts
 * 
 * diagram in 
 * 
 */

#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

SoftwareSerial BT(2, 0);

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      50

// Brightness 0 to 255
#define BRIGHTNESS 125

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel pixelss you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);



char in = ' ';
void setup() {
  BT.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(BRIGHTNESS);
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, 0, 0, 0); //black color to all
    pixels.show();
  }

}

void loop() {
  if (serialEvent()) {
    animations(); //call the function
  }
}

boolean serialEvent() {
  if (BT.available() > 0) {
    in = BT.read();
    return true;
  } else {
    return false;
  }
}
void animations() {

  switch (in) {
    case 'b':
      changecolor(0, 0, 255);
      break;
    case 'r':
      changecolor(255, 0, 0); //red
      break;
    case 'g':
      changecolor(0, 255, 0); //green
      break;  
    case 'y':
      changecolor(255, 255, 0); //yellow
      break;
    case 'c':
      changecolor(0, 255, 255); //cyan
      break;
    case 'm':
      changecolor(255, 0, 255); //magenta
      break;
    case 'w':
      changecolor(255, 255, 255); //magenta
      break;
    case 'q':
      theaterChaseRainbow(50);
      break;
    case 'a':
      rainbowCycle(50);
      break;
    case 'e':
      rainbow(50);
      break;
    default:
      changecolor(0, 0, 0);
      in=' ';
      break;
  }
}



void changecolor(byte r, byte g, byte b) {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, r, g, b); //blue color to all
    pixels.show();
    delay(20);
  }
}

void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    if(serialEvent()){
      break;
    }
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < pixels.numPixels(); i = i + 3) {
        pixels.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      pixels.show();
      delay(wait);

      for (uint16_t i = 0; i < pixels.numPixels(); i = i + 3) {
        pixels.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {  if(serialEvent()){
      break;
    }  
    for(i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
void rainbowCycle(uint8_t wait) {   
 
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    if(serialEvent()){
      break;
    }
    for (i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();

    delay(wait);
  }
}

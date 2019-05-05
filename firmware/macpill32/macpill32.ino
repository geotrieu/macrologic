/* MacroKeyboard
 * George Trieu
 * Created on: 04/30/2019
 * Last Updated on: 05/05/2019
 */
#include <USBComposite.h>
#include <WS2812B.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306_STM32.h>
#include <RGBConverter.h>

#include "bitmaps.h"

#define NUM_LEDS 9
#define OLED_ENABLE
#define OLED_RESET 4

USBHID HID;
HIDConsumer Consumer(HID);
HIDJoystick Joystick(HID);
USBCompositeSerial CompositeSerial;

const uint8_t reportDescription[] = {
   HID_CONSUMER_REPORT_DESCRIPTOR(),
   HID_JOYSTICK_REPORT_DESCRIPTOR()
};

WS2812B lights = WS2812B(NUM_LEDS);
RGBConverter rgbconv;

bool rainbowStatus = false;
uint16_t rainbow_j = 0;

#ifdef OLED_ENABLE
  Adafruit_SSD1306 display(OLED_RESET);
#endif

void setup() {
  /* PIN SETUP
   *  
   * PB8  | PB9  | PB5
   * -----------------
   * PB4  | PB3  | PA15
   * ------------------
   * PB15 | PB14 | PB13
   * 
   * ROTARY BUTTON - PB0
   */
  pinMode(PB8, INPUT_PULLUP);
  pinMode(PB9, INPUT_PULLUP);
  pinMode(PB5, INPUT_PULLUP);
  pinMode(PB4, INPUT_PULLUP);
  pinMode(PB3, INPUT_PULLUP);
  pinMode(PA15, INPUT_PULLUP);
  pinMode(PB15, INPUT_PULLUP);
  pinMode(PB14, INPUT_PULLUP);
  pinMode(PB13, INPUT_PULLUP);
  pinMode(PB0, INPUT_PULLUP);

  randomSeed(analogRead(0));

  /* WS2812 SETUP
   * 
   * 0 | 1 | 2
   * ----------
   * 5 | 4 | 3
   * ----------
   * 6 | 7 | 8
   * 
   */
  lights.begin();
  lights.show();
  delay(100);
  //Initialize all lights with white
  for (int i = 0; i < NUM_LEDS; i++) {
    lights.setPixelColor(i, 255, 255, 255);
  }
  lights.show();

  //OLED SETUP
  #ifdef OLED_ENABLE
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.drawBitmap(0, 0, macpill32, 128, 64, 1);
    display.display();
  #endif
  
  //HID Setup
  USBComposite.setProductId(52324);
  HID.begin(CompositeSerial, reportDescription, sizeof(reportDescription));
  Joystick.begin();
  delay(1000);
}

void loop() {
  if (digitalRead(PB8) == LOW) {
    Consumer.press(0xEA);
    Consumer.release();
    while (digitalRead(PB8) == LOW);
  } else if (digitalRead(PB9) == LOW) {
    Consumer.press(0xE9);
    Consumer.release();
    while (digitalRead(PB9) == LOW);
  } else if (digitalRead(PB5) == LOW) {
    Consumer.press(0xE2);
    Consumer.release();
    while (digitalRead(PB5) == LOW);
  } else if (digitalRead(PB4) == LOW) {
    Consumer.press(0xB6);
    Consumer.release();
    while (digitalRead(PB4) == LOW);
  } else if (digitalRead(PB3) == LOW) {
    Consumer.press(0xB5);
    Consumer.release();
    while (digitalRead(PB3) == LOW);
  } else if (digitalRead(PA15) == LOW) {
    Consumer.press(0xCD);
    Consumer.release();
    while (digitalRead(PA15) == LOW);
  } else if (digitalRead(PB15) == LOW) {
    Joystick.button(1, HIGH);
    rainbowStatus = false;
    randCol();
    oledPrint("Columns:", "On", "");
    while (digitalRead(PB15) == LOW);
    Joystick.button(1, LOW);
  } else if (digitalRead(PB14) == LOW) {
    Joystick.button(2, HIGH);
    rainbowStatus = false;
    randCheck();
    oledPrint("Checkers:", "On", "");
    while (digitalRead(PB14) == LOW);
    Joystick.button(2, LOW);
  } else if (digitalRead(PB13) == LOW) {
    Joystick.button(3, HIGH);
    rainbowStatus = false;
    randShade();
    oledPrint("Shade:", "On", "");
    while (digitalRead(PB13) == LOW);
    Joystick.button(3, LOW);
  } else if (digitalRead(PB0) == LOW) {
    rainbowStatus = !rainbowStatus;
    oledPrint("Rainbow:", rainbowStatus ? "True":"False", "");
    while (digitalRead(PB0) == LOW);
  }
  if (rainbowStatus) {
    for (int i = 0; i < NUM_LEDS; i++) {
      lights.setPixelColor(i, Wheel((rainbow_j) & 255));
      lights.show();
    }
    if (rainbow_j < 256) {
      rainbow_j++;
    } else {
      rainbow_j = 0;
    }
  }

  //Client Interface
  if (CompositeSerial.available()) {
    int r,g,b;
    r = readCompositeSerial().toInt();
    g = readCompositeSerial().toInt();
    b = readCompositeSerial().toInt();
    for (int i = 0; i < NUM_LEDS; i++) {
      lights.setPixelColor(i, r, g, b);
    }
    lights.show();
  }
  delay(25);
}

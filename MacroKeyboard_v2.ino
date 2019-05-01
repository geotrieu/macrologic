/* MacroKeyboard
 * George Trieu
 * Created on: 04/30/2019
 * Last Updated on: 04/30/2019
 */
#include <USBComposite.h>
#include <WS2812B.h>

#define NUM_LEDS 9

USBHID HID;
HIDConsumer Consumer(HID);
HIDJoystick Joystick(HID);
USBCompositeSerial CompositeSerial;

const uint8_t reportDescription[] = {
   HID_CONSUMER_REPORT_DESCRIPTOR(),
   HID_JOYSTICK_REPORT_DESCRIPTOR()
};

WS2812B lights = WS2812B(NUM_LEDS);

String readCompositeSerial() {
  char input;
  String test;
  while(true) {
    input = CompositeSerial.read();
    while (input != 255) { //Default Library Return for "no signal"
      if (input == 13) {
        CompositeSerial.read();
        return test; //Carrige Return
      }
      test += input;
      //CompositeSerial.println(test);
      input = CompositeSerial.read();
    }
    delay(10);
  }
  return test;
}

void setup() {
  //Pin Setup
  pinMode(PB7, INPUT_PULLUP);
  pinMode(PB6, INPUT_PULLUP);
  pinMode(PB5, INPUT_PULLUP);
  pinMode(PB4, INPUT_PULLUP);
  pinMode(PB3, INPUT_PULLUP);
  pinMode(PA15, INPUT_PULLUP);
  pinMode(PB15, INPUT_PULLUP);
  pinMode(PB14, INPUT_PULLUP);
  pinMode(PB13, INPUT_PULLUP);

  //WS2812B Setup
  lights.begin();
  lights.show();

  //HID Setup
  USBComposite.setProductId(52324);
  HID.begin(CompositeSerial, reportDescription, sizeof(reportDescription));
  Joystick.begin();
  delay(1000);
}

void loop() {
  if (digitalRead(PB7) == LOW) {
    Consumer.press(0xEA);
    Consumer.release();
    while (digitalRead(PB7) == LOW);
  } else if (digitalRead(PB6) == LOW) {
    Consumer.press(0xE9);
    Consumer.release();
    while (digitalRead(PB6) == LOW);
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
    int num1 = random(0, 255);
    int num2 = random(0, 255);
    int num3 = random(0, 255);
    for (int i = 0; i < NUM_LEDS; i++) {
      lights.setPixelColor(i, num1, num2, num3);
    }
    lights.show();
    while (digitalRead(PB15) == LOW);
    Joystick.button(1, LOW);
  } else if (digitalRead(PB14) == LOW) {
    Joystick.button(2, HIGH);
    for (int i = 0; i < NUM_LEDS; i++) {
      lights.setPixelColor(i, 0, 0, 0);
    }
    lights.show();
    while (digitalRead(PB14) == LOW);
    Joystick.button(2, LOW);
  } else if (digitalRead(PB13) == LOW) {
    Joystick.button(3, HIGH);
    for (int i = 0; i < NUM_LEDS; i++) {
      lights.setPixelColor(i, random(0,255), random(0,255), random(0,255));
    }
    lights.show();
    while (digitalRead(PB13) == LOW);
    Joystick.button(3, LOW);
  }

  delay(10);
  /*CompositeSerial.println("Enter Pin ");
  if (readCompositeSerial() == "8954") {
    CompositeSerial.println("yes");
    Consumer.press(0xE2);
    Consumer.release();
  } else {
    CompositeSerial.println("no");
  }*/
  
}

uint32_t Wheel(byte WheelPos) 
{
  if(WheelPos < 85) 
  {
    return lights.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else 
  {
    if(WheelPos < 170) 
    {
     WheelPos -= 85;
     return lights.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    } 
    else 
    {
     WheelPos -= 170;
     return lights.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
  }
}

void randColor() {
  int num1 = random(0, 255);
  int num2 = random(0, 255);
  int num3 = random(0, 255);
  for (int i = 0; i < NUM_LEDS; i++) {
    lights.setPixelColor(i, num1, num2, num3);
  }
  lights.show();
}

void randCol() {
  int num1 = random(0, 255);
  int num2 = random(0, 255);
  int num3 = random(0, 255);
  lights.setPixelColor(0, num1, num2, num3);
  lights.setPixelColor(5, num1, num2, num3);
  lights.setPixelColor(6, num1, num2, num3);
  num1 = random(0, 255);
  num2 = random(0, 255);
  num3 = random(0, 255);
  lights.setPixelColor(1, num1, num2, num3);
  lights.setPixelColor(4, num1, num2, num3);
  lights.setPixelColor(7, num1, num2, num3);
  num1 = random(0, 255);
  num2 = random(0, 255);
  num3 = random(0, 255);
  lights.setPixelColor(2, num1, num2, num3);
  lights.setPixelColor(3, num1, num2, num3);
  lights.setPixelColor(8, num1, num2, num3);
  lights.show();
}

void randCheck() {
  double hue = random(0,101)/100.0;
  double saturation = 1.0;//1.0 for brilliant, 0.0 for dull
  double luminance = 0.4; //1.0 for brighter, 0.0 for black
  byte rgb[3];
  rgbconv.hslToRgb(hue, saturation, luminance, rgb);
  lights.setPixelColor(0, rgb[0], rgb[1], rgb[2]);
  lights.setPixelColor(2, rgb[0], rgb[1], rgb[2]);
  lights.setPixelColor(4, rgb[0], rgb[1], rgb[2]);
  lights.setPixelColor(6, rgb[0], rgb[1], rgb[2]);
  lights.setPixelColor(8, rgb[0], rgb[1], rgb[2]);
  if (hue*360 > 180) {
    hue = (hue*360 - 180)/360.0;
  } else {
    hue = (hue*360 + 180)/360.0;
  }
  rgbconv.hslToRgb(hue, saturation, luminance, rgb);
  /*num1 = max(max(num1,num2),num3) + min(min(num1,num2),num3) - num1;
  num2 = max(max(num1,num2),num3) + min(min(num1,num2),num3) - num2;
  num3 = max(max(num1,num2),num3) + min(min(num1,num2),num3) - num3;*/
  lights.setPixelColor(1, rgb[0], rgb[1], rgb[2]);
  lights.setPixelColor(3, rgb[0], rgb[1], rgb[2]);
  lights.setPixelColor(5, rgb[0], rgb[1], rgb[2]);
  lights.setPixelColor(7, rgb[0], rgb[1], rgb[2]);
  lights.show();
}

void randShade() {
  int num1 = random(0, 255);
  int num2 = random(0, 255);
  int num3 = random(0, 255);
  for (int i = 0; i < 3; i++) {
    lights.setPixelColor(i, num1, num2, num3);
  }
  for (int i = 3; i < 6; i++) {
    lights.setPixelColor(i, num1/3, num2/3, num3/3);
  }
  for (int i = 6; i < 9; i++) {
    lights.setPixelColor(i, num1/6, num2/6, num3/6);
  }
  lights.show();
}

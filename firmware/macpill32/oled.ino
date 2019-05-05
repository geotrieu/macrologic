void oledPrint(String message1, String message2, String message3) {
  display.clearDisplay();
  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.println(message1);
  display.println(message2);
  display.println(message3);
  display.display();
}

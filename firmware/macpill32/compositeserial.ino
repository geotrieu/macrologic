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

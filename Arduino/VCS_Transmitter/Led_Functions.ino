/*
Byte Code for LEDs (pins Q0-Q7):
  1 = LED 0 = Power (Red)

  2 = LED 1 = Switch Position 1 (Green)
  4 = LED 2 = Switch Position 2 (Green)
  8 = LED 3 = Switch Position 3 (Green)
 16 = LED 4 = Switch Position 4 (Green)
 32 = LED 5 = Switch Position 5 (Green)

 64 = LED 6 = Wifi status (Blue)
128 = LED 7 = Status (Green)
*/

void activateLeds()
{
  updateShiftRegister();
/*
  delay(100);
  for (int i = 0; i < 8; i++)
  {
    bitSet(leds, i);
    updateShiftRegister();
    delay(100);
  }
  */
}


void updateShiftRegister()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
}

void ledPost()
{
  int seq[8] = {1,2,4,8,16,32,64,128};
  for (int i = 0; i < 5; i++) {
  for (int n = 0; n < 8; n++)
  {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, seq[n]);
    digitalWrite(latchPin, HIGH);
    delay(60);
  }
  }
}

void blinkWoDelay()
{
 
 // Blink networkPin until connection is established.
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      digitalWrite(powerPin, ledState);
    } 
  
}
